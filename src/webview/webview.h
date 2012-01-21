/* ============================================================
* QupZilla - WebKit based browser
* Copyright (C) 2010-2012  David Rosca <nowrep@gmail.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
* ============================================================ */
#ifndef WEBVIEW_H
#define WEBVIEW_H

#include <QWebView>
#include <QWebFrame>
#include <QWebElementCollection>
#include <QTouchEvent>
#include <QClipboard>
#include <QPrintPreviewDialog>
#include <QFile>

class WebView : public QWebView
{
    Q_OBJECT
public:
    explicit WebView(QWidget* parent = 0);

    QIcon icon() const;
    QString title() const;
    QUrl url() const;

    bool isLoading() const;
    int loadProgress() const;

    void addNotification(QWidget* notif);
    bool eventFilter(QObject* obj, QEvent* event);

    virtual QWidget* overlayForJsAlert() = 0;

    static bool isUrlValid(const QUrl &url);
    static QUrl guessUrlFromString(const QString &string);

signals:
    void viewportResized(QSize);
    void showNotification(QWidget*);
    void iconChanged();

public slots:
    void zoomIn();
    void zoomOut();
    void zoomReset();

    void load(const QUrl &url);
    void reload();

    void back();
    void forward();

    void selectAll();
    void printPage(QWebFrame* frame = 0);

    virtual void closeView() = 0;

protected slots:
    void slotLoadStarted();
    void slotLoadProgress(int progress);
    void slotLoadFinished();
    void slotIconChanged();

    // Context menu slots
    void openUrlInNewWindow();
    void sendLinkByMail();
    void copyLinkToClipboard();
    void downloadLinkToDisk();
    void copyImageToClipboard();
    void openActionUrl();
    void showSource(QWebFrame* frame = 0, const QString &selectedHtml = QString());
    void showSiteInfo();

protected:
    void wheelEvent(QWheelEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent* event);
    void resizeEvent(QResizeEvent* event);

    void setZoom(int zoom);
    void applyZoom();
    void copyText();
    QUrl lastUrl();

private:
    QList<int> m_zoomLevels;
    int m_currentZoom;

    QIcon m_siteIcon;
    QUrl m_siteIconUrl;

    bool m_isLoading;
    int m_progress;
    QUrl m_aboutToLoadUrl;
    QUrl m_lastUrl;

    QList<QTouchEvent::TouchPoint> m_touchPoints;
};

#endif // WEBVIEW_H
