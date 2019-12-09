#pragma once

namespace c_style_api {

    struct resource;
    struct sub_resource;

    enum resource_mode {
        SINGLE, ARRAY, UNKNOWN
    };

    resource* init_resource(resource_mode mode);

    void release_resource(resource const*);

    sub_resource* get_sub_resource(resource* handle);

}