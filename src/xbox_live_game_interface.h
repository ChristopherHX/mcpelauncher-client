#pragma once

#include <memory>
#include <minecraft/Xbox.h>
#include <log.h>

class XboxLiveGameInterface {

public:
    static XboxLiveGameInterface& getInstance();
#ifdef ENABLE_CLL
    virtual std::string getCllXToken(bool refresh) = 0;

    virtual std::string getCllXTicket(std::string const& xuid) = 0;
#endif


};

class XboxLiveDefaultGameInterface : public XboxLiveGameInterface {

protected:
    static const char* const TAG;



public:
#ifdef ENABLE_CLL
    std::string getCllXToken(bool refresh) override;

    std::string getCllXTicket(std::string const &xuid) override;
#endif

};