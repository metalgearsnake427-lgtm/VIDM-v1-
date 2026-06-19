#include <QString>
#include <QDebug>
#include <functional>

// Define the callback type matching Rust's SearchCallback
extern "C" {
    typedef void (*SearchCallback)(const char*, bool);
    void run_rust_internet_search(const char* query, SearchCallback callback);
    void free_rust_string(char* s);
}

class RustBridge : public QObject {
    Q_OBJECT
public:
    static RustBridge& instance() {
        static RustBridge _instance;
        return _instance;
    }

    void triggerSearch(const QString &query) {
        qDebug() << "[C++] Triggering Rust Search for:" << query;
        run_rust_internet_search(query.toUtf8().constData(), RustBridge::onSearchResult);
    }

    static void onSearchResult(const char* results, bool success) {
        if (success) {
            qDebug() << "[C++] Search Success:" << results;
        } else {
            qDebug() << "[C++] Search Failed:" << results;
        }
        if (results) {
            free_rust_string((char*)results);
        } else {
            qDebug() << "[C++] No results to free.";
        }
    }
};
