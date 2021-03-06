#ifndef __LIBXQ_H_INCLUDED__
#define __LIBXQ_H_INCLUDED__
/**
 * Copyright 2013-2015 Comcast Cable Communications Management, LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * A library implementing a jQuery-like interface for working with XML
 */

#include <libxml/parser.h>
#include <libxml/tree.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef enum {
  XQ_OK = 0,
  XQ_OUT_OF_MEMORY,
  XQ_ARGUMENT_OUT_OF_BOUNDS,
  XQ_XML_PARSER_ERROR,
  XQ_NO_TOKEN, // this is an internal status code
  XQ_INVALID_SEL_UNTERMINATED_STR,
  XQ_INVALID_SEL_UNEXPECTED_TOKEN,
  XQ_NO_MATCH, // this is an internal status code
  XQ_UNKNOWN_NS_PREFIX
} xQStatusCode;

typedef struct _xQNodeList {
  xmlNodePtr* list;
  unsigned long capacity;
  unsigned long size;
} xQNodeList;

xQStatusCode xQNodeList_alloc_init(xQNodeList** list, unsigned long size);
xQStatusCode xQNodeList_init(xQNodeList* list, unsigned long size);
xQStatusCode xQNodeList_free(xQNodeList* list, int freeList);
xQStatusCode xQNodeList_insert(xQNodeList* list, xmlNodePtr node, unsigned long atIdx);
xQStatusCode xQNodeList_remove(xQNodeList* list, unsigned long fromIdx, unsigned long count);
xQStatusCode xQNodeList_assign(xQNodeList* toList, xQNodeList* fromList);
#define xQNodeList_push(list, node) (xQNodeList_insert(list, node, (list)->size))
#define xQNodeList_clear(list) ((list)->size = 0)



typedef struct _xQ {
  xmlDocPtr document;
  xQNodeList context;
  xmlHashTablePtr nsPrefixes;
} xQ;

xQStatusCode xQ_alloc_init(xQ** self);
xQStatusCode xQ_alloc_initDoc(xQ** self, xmlDocPtr doc);
xQStatusCode xQ_alloc_initFile(xQ** self, const char* filename, xmlDocPtr* doc);
xQStatusCode xQ_alloc_initMemory(xQ** self, const char* buffer, int size, xmlDocPtr* doc);
xQStatusCode xQ_alloc_initNodeList(xQ** self, xQNodeList* list);
xQStatusCode xQ_init(xQ* self);
xQStatusCode xQ_free(xQ* self, int freeXQ);
xQStatusCode xQ_children(xQ* self, const xmlChar* selector, xQ** result);
xQStatusCode xQ_closest(xQ* self, const xmlChar* selector, xQ** result);
xQStatusCode xQ_find(xQ* self, const xmlChar* selector, xQ** result);
xQStatusCode xQ_filter(xQ* self, const xmlChar* selector, xQ** result);
xQStatusCode xQ_next(xQ* self, const xmlChar* selector, xQ** result);
xQStatusCode xQ_nextAll(xQ* self, const xmlChar* selector, xQ** result);
xQStatusCode xQ_nextUntil(xQ* self, const xmlChar* selector, xQ** result);
xQStatusCode xQ_not(xQ* self, const xmlChar* selector, xQ** result);
xQStatusCode xQ_parent(xQ* self, const xmlChar* selector, xQ** result);
xQStatusCode xQ_parents(xQ* self, const xmlChar* selector, xQ** result);
xQStatusCode xQ_parentsUntil(xQ* self, const xmlChar* selector, xQ** result);
xQStatusCode xQ_prev(xQ* self, const xmlChar* selector, xQ** result);
xQStatusCode xQ_prevAll(xQ* self, const xmlChar* selector, xQ** result);
xQStatusCode xQ_prevUntil(xQ* self, const xmlChar* selector, xQ** result);
xQStatusCode xQ_clear(xQ* self);
unsigned long xQ_length(xQ* self);
xmlChar* xQ_getText(xQ* self);
xmlChar* xQ_getAttr(xQ* self, const char* name);
xmlChar* xQ_getXml(xQ* self);
xQStatusCode xQ_first(xQ* self, xQ** result);
xQStatusCode xQ_last(xQ* self, xQ** result);
xQStatusCode xQ_addNamespace(xQ* self, const xmlChar* prefix, const xmlChar* uri);
const xmlChar* xQ_namespaceForPrefix(xQ* self, const xmlChar* prefix);



typedef xQStatusCode (*xQSearchOp)(xQ* context, xmlChar** args, xmlNodePtr node, xQNodeList* outList);
typedef struct _xQSearchExpr xQSearchExpr;
struct _xQSearchExpr {
  unsigned int argc;
  xmlChar** argv;
  xQSearchOp operation;
  xQSearchExpr* next;
};

xQStatusCode xQSearchExpr_alloc_init(xQSearchExpr** self, const xmlChar* expr);
xQStatusCode xQSearchExpr_alloc_initFilter(xQSearchExpr** self, const xmlChar* expr);
xQStatusCode xQSearchExpr_free(xQSearchExpr* self);
xQStatusCode xQSearchExpr_eval(xQSearchExpr* self, xQ* context, xmlNodePtr node, xQNodeList* outList);

xQStatusCode _xQ_findDescendants(xQ* context, xmlChar** args, xmlNodePtr node, xQNodeList* outList);
xQStatusCode _xQ_findDescendantsByName(xQ* context, xmlChar** args, xmlNodePtr node, xQNodeList* outList);
xQStatusCode _xQ_findChildrenByName(xQ* context, xmlChar** args, xmlNodePtr node, xQNodeList* outList);
xQStatusCode _xQ_findNextSiblingByName(xQ* context, xmlChar** args, xmlNodePtr node, xQNodeList* outList);
xQStatusCode _xQ_filterAttributeEquals(xQ* context, xmlChar** args, xmlNodePtr node, xQNodeList* outList);
xQStatusCode _xQ_addToOutput(xQ* context, xmlChar** args, xmlNodePtr node, xQNodeList* outList);
xQStatusCode _xQ_filterByName(xQ* context, xmlChar** args, xmlNodePtr node, xQNodeList* outList);

extern const xmlChar* XQ_EMPTY_NAMESPACE;

#ifdef __cplusplus
}
#endif

#endif // __LIBXQ_H_INCLUDED__
