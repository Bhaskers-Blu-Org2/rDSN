/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Microsoft Corporation
 * 
 * -=- Robust Distributed System Nucleus (rDSN) -=- 
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/*
 * Description:
 *     What is this file about?
 *
 * Revision history:
 *     xxxx-xx-xx, author, first version
 *     xxxx-xx-xx, author, fix bug about xxx
 */

#pragma once

# include <dsn/service_api_cpp.h>
# include <dsn/dist/replication/replication.types.h>
# include <dsn/dist/replication/replication_other_types.h>
# include <dsn/dist/replication/replication.codes.h>

namespace dsn
{
    namespace replication 
    {
        // seems thrift does not define this, why!!!!
        inline bool global_partition_id::operator < (const global_partition_id & r) const
        {
            return app_id < r.app_id || (app_id == r.app_id && pidx < r.pidx);
        }
        /*
#ifndef DSN_NOT_USE_DEFAULT_SERIALIZATION
        inline bool operator == (const global_partition_id& l, const global_partition_id& r)
        {
            return l.app_id == r.app_id && l.pidx == r.pidx;
        }
#endif*/

        inline int gpid_to_hash(global_partition_id gpid)
        {
            return static_cast<int>(gpid.app_id ^ gpid.pidx);
        }
    }
}

namespace std
{
    template<>
    struct hash< ::dsn::replication::global_partition_id> {
        size_t operator()(const ::dsn::replication::global_partition_id &gpid) const {
            return std::hash<int>()(gpid.app_id) ^ std::hash<int>()(gpid.pidx);
        }
    };
}
