//
//  Graph.mm
//  OpenGraph_SPI

#include "Graph.hpp"
#include "Subgraph.hpp"
#include "OGGraphDescription.h"

#if OG_OBJC_FOUNDATION
#include <dispatch/dispatch.h>
#include <pthread.h>
#include <Foundation/Foundation.h>
#include <zlib.h>

pthread_key_t OG::Graph::_current_update_key;

OG::Graph::Graph() OG_NOEXCEPT {
    // TODO
    
    // libdispatch is not supported on WASI
    // Tracked via https://github.com/swiftwasm/swift/issues/5565
    #if !OG_TARGET_OS_WASI
    static dispatch_once_t make_keys;
    dispatch_once_f(&make_keys, nullptr, [](void * _Nullable context){
        pthread_key_create(&_current_update_key, nullptr);
        OG::Subgraph::make_current_subgraph_key();
    });
    #endif
    
    // TODO
}

const void OG::Graph::value_mark_all() const OG_NOEXCEPT {
    // TODO
}

void OG::Graph::all_start_profiling(uint32_t) OG_NOEXCEPT {
    // TODO
}
void OG::Graph::all_stop_profiling() OG_NOEXCEPT {
    // TODO
}
void OG::Graph::start_profiling(uint32_t) OG_NOEXCEPT {
    // TODO
}
void OG::Graph::stop_profiling() OG_NOEXCEPT {
    // TODO
}

void OG::Graph::write_to_file(const Graph * _Nullable graph, const char * _Nullable name, uint8_t options) OG_NOEXCEPT {
    @autoreleasepool {
        NSDictionary <NSString *, id> *options_dict = @{
            (__bridge NSString *)OGDescriptionFormat: (__bridge NSString *)OGDescriptionFormatDictionary,
            (__bridge NSString *)OGDescriptionIncludeValues: @((options & 1) == 0),
            (__bridge NSString *)OGDescriptionAllGraphs: @(graph == nil)
        };
        NSString *description = (__bridge NSString *)Graph::description(graph, options_dict);
        if (description == nil) {
            return;
        }
        const char *cstring_name = name ?: "graph.ag-gzon";

        NSData *data = [NSJSONSerialization dataWithJSONObject:description options:0 error:nil];
        NSString *file_path = [NSString stringWithUTF8String:cstring_name];
        if (cstring_name[0] != '/') {
            file_path = [NSTemporaryDirectory() stringByAppendingPathComponent:file_path];
        }
        NSError *error = nil;
        BOOL success = YES;
        if ([file_path.pathExtension isEqualToString:@"ag-gzon"]) {
            gzFile file = gzopen(file_path.fileSystemRepresentation, "wb");
            if (file != NULL) {
                const char *bytes = (const char *)[data bytes];
                NSUInteger remaining = [data length];
                while (remaining != 0) {
                    int bytes_written = gzwrite(file, bytes, (unsigned int)remaining);
                    if (bytes_written <= 0) {
                        success = NO;
                        break;
                    }
                    bytes += bytes_written;
                    remaining -= bytes_written;
                }
                gzclose(file);
            }
        } else {
            success = [data writeToFile:file_path options:0 error:&error];
        }
        if (success) {
            fprintf(stderr, "Wrote graph data to \"%s\".\n", file_path.UTF8String);
        } else {
            fprintf(stderr, "Unable to write to \"%s\": %s\n", file_path.UTF8String, error.description.UTF8String);
        }
    }
}

const bool OG::Graph::thread_is_updating() const OG_NOEXCEPT {
    void *current = pthread_getspecific(current_key());
    if (!current) {
        return false;
    }
    // TODO
    return false;
}

const bool OG::Graph::is_context_updating(const OG::Graph::Context&) const OG_NOEXCEPT {
    // TODO
    return false;
}
#endif /* OG_OBJC_FOUNDATION */
