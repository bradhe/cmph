#ifndef __CMPH_H__
#define __CMPH_H__

#include <stdlib.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif

#include "cmph_types.h"

typedef struct __config_t cmph_config_t;
typedef struct __cmph_t cmph_t;

typedef struct 
{
	void *data;
	cmph_uint32 nkeys;
	int (*read)(void *, char **, cmph_uint32 *);
	void (*dispose)(void *, char *, cmph_uint32);
	void (*rewind)(void *);
} cmph_io_adapter_t;

/** Adapter pattern API **/
/* please call free() in the created adapters */
cmph_io_adapter_t *cmph_io_nlfile_adapter(FILE * keys_fd);
cmph_io_adapter_t *cmph_io_nlnkfile_adapter(FILE * keys_fd, cmph_uint32 nkeys);
/*cmph_io_adapter_t *cmph_io_vector_adapter(const char ** vector, cmph_uint32 nkeys);*/

/** Hash configuration API **/
cmph_config_t *cmph_config_new(cmph_io_adapter_t *key_source);
void cmph_config_set_hashfuncs(cmph_config_t *mph, CMPH_HASH *hashfuncs);
void cmph_config_set_verbosity(cmph_config_t *mph, cmph_uint32 verbosity);
void cmph_config_set_graphsize(cmph_config_t *mph, float c);
void cmph_config_set_algo(cmph_config_t *mph, CMPH_ALGO algo);
void cmph_config_set_ncomponents(cmph_config_t *mph, cmph_uint32 K);
void cmph_config_destroy(cmph_config_t *mph);

/** Hash API **/
cmph_t *cmph_new(cmph_config_t *mph);
cmph_uint32 cmph_search(cmph_t *mphf, const char *key, cmph_uint32 keylen);
cmph_uint32 cmph_size(cmph_t *mphf);
void cmph_destroy(cmph_t *mphf);

/** Hash serialization/deserialization */
int cmph_dump(cmph_t *mphf, FILE *f);
cmph_t *cmph_load(FILE *f);

#ifdef __cplusplus
}
#endif

#endif
