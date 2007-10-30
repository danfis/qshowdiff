#include <QVBoxLayout>
#include <QScrollBar>
#include <QPainter>
#include <QScrollArea>

#include "../debug.h"
#include "../settings.h"
#include "diff_view.h"
#include "diff_view.moc"

DiffViewFrame::DiffViewFrame(QWidget *parent) : QWidget(parent)
{
	QVBoxLayout *layout = new QVBoxLayout();
    QSplitter *splitter = new QSplitter(Qt::Horizontal);
    _original = new DiffView(true);
    _modified = new DiffView(false);
    QScrollArea *orig = new QScrollArea();
    QScrollArea *modif = new QScrollArea();

    
    orig->setWidget(_original);
    orig->setWidgetResizable(true);
    orig->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    modif->setWidget(_modified);
    modif->setWidgetResizable(true);

    splitter->addWidget(orig);
    splitter->addWidget(modif);

    layout->addWidget(splitter);

	setLayout(layout);


    QScrollBar *orig_vertical = orig->verticalScrollBar();
    QScrollBar *modif_vertical = modif->verticalScrollBar();
    QScrollBar *orig_horizontal = orig->horizontalScrollBar();
    QScrollBar *modif_horizontal = modif->horizontalScrollBar();

    connect(orig_vertical, SIGNAL(valueChanged(int)), modif_vertical,
            SLOT(setValue(int)));
    connect(modif_vertical, SIGNAL(valueChanged(int)), orig_vertical,
            SLOT(setValue(int)));
    connect(orig_horizontal, SIGNAL(valueChanged(int)), modif_horizontal,
            SLOT(setValue(int)));
    connect(modif_horizontal, SIGNAL(valueChanged(int)), orig_horizontal,
            SLOT(setValue(int)));
}

void DiffViewFrame::changeFile(int num) const
{
    if (num != -1){
        // num - 1 is there because num==0 is for 'All files'
        _original->setCurrentFile(num - 1);
        _modified->setCurrentFile(num - 1);
    }
}

/* DiffView */
void DiffView::paintEvent(QPaintEvent *e)
{
    painter = new QPainter(this);
    offset = 0;
    max_width = 0;

    _paintFiles();
    
    setFixedHeight(offset);
    setMinimumWidth(max_width);
    delete painter;
}

void DiffView::setCurrentFile(int num)
{
    _current_file = num;
    repaint();
}




void DiffView::_paintFiles()
{
    if (_current_file == -1){
        Diff::const_iterator it = Diff::instance()->begin();
        Diff::const_iterator it_end = Diff::instance()->end();

        for (;it != it_end; it++){
            _paintFileHeader((*it)->getFilename());
            _paintHunks(*it);
        }
    }else{
        Diff *diff = Diff::instance();

        if (diff->numFiles() > _current_file){
            File const *file = diff->getFile(_current_file);
            _paintFileHeader(file->getFilename());
            _paintHunks(file);
        } // else do nothing
    }
}

void DiffView::_paintHunks(File const *file)
{
    File::const_iterator it = file->begin();
    File::const_iterator it_end = file->end();

    for (; it != it_end; it++){
        _paintHunkHeader();
        _paintSnippets(*it);
    }
}

void DiffView::_paintSnippets(Hunk const *hunk)
{
    int from_line;
    int height = QFontMetrics(Settings::Text::font).height();
    Hunk::const_iterator it = hunk->begin();
    Hunk::const_iterator it_end = hunk->end();

    if (_original)
        from_line = hunk->originalBeginsAt();
    else
        from_line = hunk->modifiedBeginsAt();

    for (; it != it_end; it++){
        _paintSnippetBackground(*it);
        if (_original){
            _paintText((*it)->getOriginal(), from_line);
            from_line += (*it)->numOriginalLines();
        }else{
            _paintText((*it)->getModified(), from_line);
            from_line += (*it)->numModifiedLines();
        }
        offset += height * (*it)->numLines();
    }
}


void DiffView::_paintText(Text const *text, int from_line)
{
    int offset = this->offset;

    QFontMetrics metrics = QFontMetrics(Settings::Text::font);
    int height = metrics.height();

    QRect line_rect(0, offset, Settings::Text::line_column_width, height);
    QRect text_rect(Settings::Text::line_column_width +
            Settings::Text::line_indentation, offset,
            painter->window().width(), height);
    int line = 0;

    painter->setBrush(Qt::NoBrush);
    painter->setPen(Settings::Text::font_color);
    painter->setFont(Settings::Text::font);
    
    Text::const_iterator it = text->begin();
    Text::const_iterator it_end = text->end();
    for (;it != it_end; it++, line++){
        painter->drawText(line_rect, Qt::AlignRight,
                QString::number(from_line));
        line_rect.moveTo(line_rect.x(), line_rect.y() + height);
        from_line++;

        max_width = std::max(max_width, metrics.width(**it));
        text_rect.setWidth(max_width);
        painter->drawText(text_rect, Qt::AlignLeft, **it);
        text_rect.moveTo(text_rect.x(), text_rect.y() + height);
        offset += height;
    }
}


void DiffView::_paintFileHeader(const QString &filename)
{
    QRect rect(0, offset, painter->window().width(),
            Settings::File::box_height);
    QRect text_rect(0 + Settings::File::text_left_indentation, offset,
            painter->window().width(), Settings::File::box_height);

    // Rectangle
    painter->setBrush(QBrush(Settings::File::background_color));
    painter->setPen(Settings::File::background_color);
    painter->drawRect(rect);

    // Text 
    painter->setFont(Settings::File::font);
    painter->setPen(Settings::File::font_color);
    painter->drawText(text_rect, Qt::AlignVCenter, "Filename: " + filename);

    offset += Settings::File::box_height;
}

void DiffView::_paintHunkHeader()
{
    painter->setBrush(QBrush(Settings::Hunk::separator_color));
    painter->setPen(Settings::Hunk::separator_color);
    painter->drawRect(0, offset, painter->window().width(),
            Settings::Hunk::separator_height);

    offset += Settings::Hunk::separator_height;
}

void DiffView::_paintSnippetBackground(Snippet const *snippet)
{
    int lines = snippet->numLines(); 
    int height = QFontMetrics(Settings::Text::font).height();
    QColor color;

    if (snippet->isContext()){
        color = Settings::Text::background_color;
    }else if (snippet->isAdded()){
        color = Settings::Text::background_color_added;
    }else if (snippet->isDeleted()){
        color = Settings::Text::background_color_deleted;
    }else if (snippet->isChanged()){
        color = Settings::Text::background_color_changed;
    }

    painter->setBrush(QBrush(color));
    painter->setPen(color);
    painter->drawRect(0, offset, painter->window().width(), lines*height);
}
