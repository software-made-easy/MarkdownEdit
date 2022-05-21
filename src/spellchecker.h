#ifndef SPELLCHECKER_H
#define SPELLCHECKER_H

#include <QSyntaxHighlighter>
#include <QPlainTextEdit>

#include <enchant++.h>

#include "markdownhighlighter.h"


class SpellChecker : public MarkdownHighlighter
{
    Q_OBJECT
public:
    explicit SpellChecker(QPlainTextEdit *parent = nullptr, const QString &lang = "");

    void highlightBlock(const QString &text) Q_DECL_OVERRIDE;

    Q_REQUIRED_RESULT const QStringList getLanguageList();

    inline QString getLanguage() { return language; };

    Q_REQUIRED_RESULT bool isCorrect(const QString &);
    Q_REQUIRED_RESULT QStringList getSuggestion(const QString &);
    void addWort(const QString &);
    void ignoreWord(const QString &);


public slots:
    inline void setMarkdownHighlightingEnabled(const bool &enabled) {markdownhig = enabled; };
    inline void setSpellCheckingEnabled(const bool &enabled) {spellingEnabled = enabled; };
    bool setLanguage(const QString &);

    void checkSpelling(const QString &);

private slots:
    void slotAddWord();
    void slotIgnoreWord();
    void slotSetLanguage(const bool &);
    void slotReplaceWord();
    void slotShowContextMenu(const QPoint &pos);

private:
    bool spellingEnabled = true;
    bool markdownhig = true;

    void showContextMenu(QMenu *menu, const QPoint &pos, int wordpos);

    QTextCharFormat spellFormat;

    QString language;
    void replaceWord(const int &wordPos, const QString &newWord);

    QPlainTextEdit *textEdit;

    QString encodeLanguageString(const QString &langString);

    enchant::Dict *speller = nullptr;
};

#endif // SPELLCHECKER_H