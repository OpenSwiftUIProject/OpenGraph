//
//  OGTrace.h
//  OpenGraphCxx

#ifndef OGTrace_h
#define OGTrace_h

#include <OpenGraph/OGBase.h>
#include <OpenGraph/OGGraph.h>

OG_ASSUME_NONNULL_BEGIN

typedef OG_ENUM(uint64_t, OGTraceEvents) {
    OGTraceEventsCustom = 1,
    OGTraceEventsNamed = 2,
    OGTraceEventsDeadline = 3,
    OGTraceEventsCompareFailed = 4,
} OG_SWIFT_NAME(TraceEvents);

typedef struct OGTrace {
    OGTraceEvents events;

    void (*_Nullable begin_trace)(void *_Nullable context, OGGraphRef graph);
    void (*_Nullable end_trace)(void *_Nullable context, OGGraphRef graph);

    void (*_Nullable begin_update_subgraph)(void *_Nullable context, OGSubgraphRef subgraph, uint32_t options);
    void (*_Nullable end_update_subgraph)(void *_Nullable context, OGSubgraphRef subgraph);
    void (*_Nullable begin_update_stack)(void *_Nullable context, OGAttribute attribute);
    void (*_Nullable end_update_stack)(void *_Nullable context, bool changed);
    void (*_Nullable begin_update_attribute)(void *_Nullable context, OGAttribute attribute);
    void (*_Nullable end_update_attribute)(void *_Nullable context, OGAttribute attribute, bool changed);
    void (*_Nullable begin_update_graph)(void *_Nullable context, OGGraphRef graph);
    void (*_Nullable end_update_graph)(void *_Nullable context, OGGraphRef graph);

    void (*_Nullable begin_invalidation)(void *_Nullable context, OGGraphRef graph, OGAttribute attribute);
    void (*_Nullable end_invalidation)(void *_Nullable context, OGGraphRef graph, OGAttribute attribute);

    void (*_Nullable begin_modify)(void *_Nullable context, OGAttribute attribute);
    void (*_Nullable end_modify)(void *_Nullable context, OGAttribute attribute);

    void (*_Nullable begin_event)(void *_Nullable context, OGAttribute attribute, const char *event_name);
    void (*_Nullable end_event)(void *_Nullable context, OGAttribute attribute, const char *event_name);

    void (*_Nullable created_graph)(void *_Nullable context, OGGraphRef graph);
    void (*_Nullable destroy_graph)(void *_Nullable context, OGGraphRef graph);
    void (*_Nullable needs_update)(void *_Nullable context, OGGraphRef graph);

    void (*_Nullable created_subgraph)(void *_Nullable context, OGSubgraphRef subgraph);
    void (*_Nullable invalidate_subgraph)(void *_Nullable context, OGSubgraphRef subgraph);
    void (*_Nullable add_child_subgraph)(void *_Nullable context, OGSubgraphRef subgraph, OGSubgraphRef child);
    void (*_Nullable remove_child_subgraph)(void *_Nullable context, OGSubgraphRef subgraph, OGSubgraphRef child);

    void (*_Nullable added_attribute)(void *_Nullable context, OGAttribute attribute);
    void (*_Nullable add_edge)(void *_Nullable context, OGAttribute attribute, OGAttribute input, unsigned int flags);
    void (*_Nullable remove_edge)(void *_Nullable context, OGAttribute attribute, size_t index);
    void (*_Nullable set_edge_pending)(void *_Nullable context, OGAttribute attribute, OGAttribute input, bool pending);

    void (*_Nullable set_dirty)(void *_Nullable context, OGAttribute attribute, bool dirty);
    void (*_Nullable set_pending)(void *_Nullable context, OGAttribute attribute, bool pending);
    void (*_Nullable set_value)(void *_Nullable context, OGAttribute attribute);
    void (*_Nullable mark_value)(void *_Nullable context, OGAttribute attribute);

    void (*_Nullable added_indirect_attribute)(void *_Nullable context, OGAttribute attribute);
    void (*_Nullable set_source)(void *_Nullable context, OGAttribute attribute, OGAttribute source);
    void (*_Nullable set_dependency)(void *_Nullable context, OGAttribute attribute, OGAttribute dependency);

    void (*_Nullable mark_profile)(void *_Nullable context, const char *event_name);

    void (*_Nullable custom_event)(void *_Nullable context, OGGraphRef graph, const char *event_name, const void *value,
                                   OGTypeID type);
    void (*_Nullable named_event)(void *_Nullable context, OGGraphRef graph, uint32_t eventID, uint32_t eventArgCount,
                                  const void *eventArgs, CFDataRef data, uint32_t arg6);
    bool (*_Nullable named_event_enabled)(void *_Nullable context);

    void (*_Nullable set_deadline)(void *_Nullable context);
    void (*_Nullable passed_deadline)(void *_Nullable context);

    void (*_Nullable compare_failed)(void *_Nullable context, OGAttribute attribute, OGComparisonState comparisonState);
} OGTrace OG_SWIFT_NAME(Trace);

OG_ASSUME_NONNULL_END

#endif /* OGTrace_h */
