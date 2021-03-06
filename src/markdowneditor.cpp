#include "markdowneditor.h"
#include "qdir.h"
#include "qlocale.h"
#include "qmessagebox.h"
#include "spellchecker.h"
#include "settings.h"

#include <QDialog>
#include <QHBoxLayout>
#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include <QMimeData>
#include <QImageReader>


MarkdownEditor::MarkdownEditor(QWidget *parent)
    : QMarkdownTextEdit(parent, false)
{
    checker = new SpellChecker(new TextEditProxyT(this));
    connect(checker, &SpellChecker::languageChanged,
            this, &MarkdownEditor::onLanguageChanged);

    setAcceptDrops(true);
}

void MarkdownEditor::dragEnterEvent(QDragEnterEvent *event)
{
    event->accept();
}

void MarkdownEditor::dragMoveEvent(QDragMoveEvent *event)
{
    event->accept();
}

void MarkdownEditor::dropEvent(QDropEvent *event)
{
    const QMimeData *data = event->mimeData();

    if (!data->hasUrls())
        return event->ignore();

    const QList<QUrl> files = data->urls();

    QDir dir;

    for (int i = 0; files.count() > i; i++) {
        QTextCursor c = cursorForPosition(event->pos());

        const QUrl file = files.at(i);
        const QString path = dir.relativeFilePath(file.toLocalFile());

        if (QImageReader::imageFormat(file.toLocalFile()).isEmpty()) {
            c.insertText(path + QLatin1Char('\n'));
            continue;
        }

        c.insertText(QStringLiteral("![%1](%2)\n").arg(file.fileName(),
                                                    path));
    }
    event->accept();
}

bool MarkdownEditor::setLanguage(const QString &lang)
{
    if (SpellChecker::getLanguageList().contains(lang))
        return checker->setLanguage(lang);
    else
        return false;
}

QString MarkdownEditor::filePath()
{
    if (getDir() == QLatin1Char('.'))
        return getFileName() + QLatin1String("[*]");
    else {
        QFileInfo info(fileName);
        return QStringLiteral("%1[*] (%2)").arg(info.fileName(),
                                                info.path()).replace(common::homeDict(),
                                                                     QChar('~'));
    }
}

QString MarkdownEditor::getFileName()
{
    return QFileInfo(fileName).fileName();
}

QString MarkdownEditor::getDir()
{
    return QFileInfo(fileName).path();
}

void MarkdownEditor::changeSpelling(const bool &c)
{
    checker->setSpellCheckingEnabled(c);
}

void MarkdownEditor::onLanguageChanged(const QString &l)
{
    if (!fileName.isEmpty()) {
        setMapAttribute(fileName, l);
    }
}

void MarkdownEditor::showMarkdownSyntax()
{
    QDialog d;
    QHBoxLayout l(&d);
    d.setLayout(&l);
    l.setContentsMargins(0, 0, 0, 0);

    MarkdownEditor e(&d);

    QString file = QLatin1String(":/syntax_en.md");
    QString language = QLatin1String("en_US");

    for (const QString &lang : common::languages()) {
        if (QFile::exists(QStringLiteral(":/syntax_%1.md").arg(lang))) {
            file = QStringLiteral(":/syntax_%1.md").arg(lang);
            language = lang;
            break;
        }
    }

    QFile f(file, &d);
    if (!f.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(&d, tr("Couldn't open file"),
                             tr("Could not open file %1: %2").arg(
                                 QDir::toNativeSeparators(file), f.errorString()));
    }
    e.setText(f.readAll());
    e.setReadOnly(true);
    if (!e.setLanguage(language))
        e.setLanguage(QLocale::system().name());
    l.addWidget(&e);

    d.showMaximized();
    d.exec();
}

void MarkdownEditor::setText(const QString &t, const QString &newFile, const bool setLangugae)
{
    if (!setLangugae) {
        if (checker)
            checker->clearDirtyBlocks();

        return QMarkdownTextEdit::setPlainText(t);
    }

    if (!newFile.isEmpty())
        fileName = newFile;

    if (fileName == QLatin1String(":/default.md") && !mapContains(fileName))
        setMapAttribute(fileName, QLatin1String("en-US"));

    if (checker) {
        checker->clearDirtyBlocks();
        checker->setDocument(nullptr);
        if (mapContains(fileName))
            setLanguage(mapAttribute(fileName));
    }

    QMarkdownTextEdit::setPlainText(t);

    checker->setDocument(document());

    document()->setModified(false);
}

MarkdownEditor::~MarkdownEditor()
{
    // delete checker;
}
