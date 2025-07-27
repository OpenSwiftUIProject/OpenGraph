//
//  Graph.mm
//  OpenGraph_SPI

#include "Graph.hpp"
#include "OGGraphDescription.h"

#if OG_OBJC_FOUNDATION
#include <Foundation/Foundation.h>
#include <zlib.h>

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

#endif /* OG_OBJC_FOUNDATION */
