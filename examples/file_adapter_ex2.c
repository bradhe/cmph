#include <cmph.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

 // Create minimal perfect hash function from in-disk keys using BMZ algorithm
int main(int argc, char **argv)
{   
	 //Open file with newline separated list of keys
	FILE * keys_fd = fopen("keys.txt", "r");
	cmph_t *hash = NULL;
	if (keys_fd == NULL) 
	{
	  fprintf(stderr, "File \"keys.txt\" not found\n");
	  exit(1);
	}	
	// Source of keys
	cmph_io_adapter_t *source = cmph_io_nlfile_adapter(keys_fd, UINT_MAX);

	cmph_config_t *config = cmph_config_new(CMPH_BMZ);
	hash = cmph_new(config, source);
	cmph_config_destroy(config);
	cmph_io_nlfile_adapter_destroy(source);
   
	//Find key
	const char *key = "jjjjjjjjjj";
	unsigned int id = cmph_search(hash, key, strlen(key));
	fprintf(stderr, "Id:%u\n", id);
	//Destroy hash
	cmph_destroy(hash);
	free(source);   
	fclose(keys_fd);
	return 0;
}
