#pragma once

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <vector>

class tracker : public QWidget {
    Q_OBJECT

public:
    tracker(QWidget* parent = nullptr);
    ~tracker() noexcept;

public slots:
    void start() noexcept;  //!< Set start time.
    void end();             //!< Export data to csv.
    void trackEvent();      //!< Add current time to events.

protected:
    void setConnections();

private:
    QVBoxLayout* lMain;
    QHBoxLayout* lButtons;

    QPushButton* bStart;
    QPushButton* bTracker;
    QPushButton* bEnd;

    bool started = false;
    std::chrono::time_point<std::chrono::system_clock> startTime;
    std::vector<long> events;
};