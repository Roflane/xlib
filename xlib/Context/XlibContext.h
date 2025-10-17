#pragma once
#include "../../libbase/libbase.h"

struct XlibContext {
private:
    bool _rdseedSupported = false;
    bool _rdrandSupported = false;
public:
    XlibContext() {
        _rdseedSupported = SupportsRdseed();
        _rdrandSupported = SupportsRdrand();
    }

    [[nodiscard]] bool getRdseedSupported() const { return _rdseedSupported; }
    [[nodiscard]] bool getRdrandSupported() const { return _rdrandSupported; }
};

namespace xlib {
    static XlibContext xlib_context;
}
