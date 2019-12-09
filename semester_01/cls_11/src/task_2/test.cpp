#include "c_style_api.hpp"
#include "cpp_wrappers.hpp"

#include <cassert>

struct c_style_api::sub_resource {
    int sub_resource_field;
};

struct c_style_api::resource {
    explicit resource(resource_mode mode) : mode(mode) {
        if (mode == ARRAY) {
            resource_field += 1;
            sub.sub_resource_field += 1;
        }
    }

    ~resource() {
        assert(is_properly_cleared);
    }

    mutable bool is_properly_cleared {false};
    c_style_api::resource_mode mode;
    int resource_field {0};
    sub_resource sub {0};
};

c_style_api::resource* c_style_api::init_resource(c_style_api::resource_mode mode) {
    switch (mode) {
        case SINGLE:
            return new resource{mode};
        case ARRAY:
            return new resource[1]{resource{mode}};
        default:
            return nullptr;
    }
}

void c_style_api::release_resource(c_style_api::resource const* res) {
    if (res) {
        res->is_properly_cleared = true;
        switch (res->mode) {
            case SINGLE:
                delete res;
                break;
            case ARRAY:
                delete[] res;
                break;
            default:
                break;
        }
    }
}

c_style_api::sub_resource* c_style_api::get_sub_resource(c_style_api::resource* handle) {
    return handle ? &(handle->sub) : nullptr;
}

static void test_resource_as_shared_ptr() {
    {
        std::shared_ptr<c_style_api::resource> ptr = cls_11::acquire_resource(c_style_api::SINGLE);

        assert(ptr->resource_field == 0);
    }

    {
        std::shared_ptr<c_style_api::resource> first = cls_11::acquire_resource(c_style_api::SINGLE);
        std::shared_ptr<c_style_api::resource> second = cls_11::acquire_resource(c_style_api::SINGLE);

        assert(first.get() != second.get());
    }

    {
        std::shared_ptr<c_style_api::resource> ptr = cls_11::acquire_resource(c_style_api::ARRAY);

        assert(ptr->resource_field == 1);
    }

    {
        std::shared_ptr<c_style_api::resource> ptr = cls_11::acquire_resource(c_style_api::UNKNOWN);

        assert(!ptr);
    }

    {
        std::shared_ptr<c_style_api::sub_resource> sub_ptr = cls_11::acquire_sub_resource(c_style_api::SINGLE);

        assert(sub_ptr->sub_resource_field == 0);
    }

    {
        std::shared_ptr<c_style_api::sub_resource> sub_ptr = cls_11::acquire_sub_resource(c_style_api::ARRAY);

        assert(sub_ptr->sub_resource_field == 1);
    }

    {
        std::shared_ptr<c_style_api::sub_resource> sub_ptr = cls_11::acquire_sub_resource(c_style_api::UNKNOWN);

        assert(!sub_ptr);
    }

    {
        std::shared_ptr<c_style_api::resource> ptr = cls_11::acquire_resource(c_style_api::SINGLE);
        std::shared_ptr<c_style_api::sub_resource> sub_ptr = cls_11::get_sub_resource(ptr);

        assert(c_style_api::get_sub_resource(ptr.get()) == sub_ptr.get());

        auto ptr_raw = ptr.get();
        ptr.reset();

        assert(sub_ptr->sub_resource_field == 0);
        assert(!ptr_raw->is_properly_cleared);
    }

    {
        assert(!cls_11::get_sub_resource({}));
    }
}

int main() {
    test_resource_as_shared_ptr();
}