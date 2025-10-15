#ifndef DEVICE_MOSQUITTOCLIENTWRAPPER_H
#define DEVICE_MOSQUITTOCLIENTWRAPPER_H

#include <mosquitto.h>
#include <stdexcept>

class MosquittoClientWrapper {
public:
    // Constructor: initializes the mosquitto client
    explicit MosquittoClientWrapper(const char* id, bool clean_session = true, void* obj = nullptr) {
        _client = mosquitto_new(id, clean_session, obj);
        if (!_client) {
            // Handle error if mosquitto_new fails
            throw std::runtime_error("Failed to create mosquitto client.");
        }
    }

    // Destructor: destroys the mosquitto client
    ~MosquittoClientWrapper() {
        if (_client) {
            mosquitto_destroy(_client);
        }
    }

    // Prevent copying to ensure single ownership
//    MosquittoClientWrapper(const MosquittoClientWrapper&) = delete;
//    MosquittoClientWrapper& operator=(const MosquittoClientWrapper&) = delete;

    mosquitto* getClient() {
        return _client;
    }

private:
    mosquitto* _client;
};

#endif //DEVICE_MOSQUITTOCLIENTWRAPPER_H
