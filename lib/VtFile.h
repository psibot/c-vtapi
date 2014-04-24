#ifndef VT_FILE_SCAN_H
#define VT_FILE_SCAN_H 1

#include <stdbool.h>

#ifdef  __cplusplus
extern "C" {
#endif

// forward declarations
struct VtFile;
struct VtObject;

/**
* @ingroup VtApiPage
* @defgroup VtFile  VtFile object for scanning files.
* @{
*/


/**
 * @brief Create a new file object
 *
 * @param  ...
 * @return VtFile*  object pointer. or NULL on error allocating
 */
struct VtFile* VtFile_new(void);


/**
 * @brief Get a reference counter
 *
 * @param FileScan ...
 * @return void
 */
void VtFile_get(struct VtFile *FileScan);



/**
 * @brief Put a reference counter
 *
 * @param FileScan ...
 * @return void
 */
void VtFile_put(struct VtFile **FileScan);

/**
 * @brief Set API Key
 * 
 * @param file_obj VtFile object pointer
 * @param api_key  Your API key
 * @return void
 */
void VtFile_setApiKey(struct VtFile *file_obj, const char *api_key);


/**
 * @brief Set the offset for the file/search  API.
 *
 * @param file_obj Object pointer
 * @param offset Offset string returned by virustotal.
 * @return void
 */
void VtFile_setOffset(struct VtFile *file_obj, const char *offset);

/**
 * @brief Scan a file
 *
 * @param file_obj file object
 * @param file_path  path to file for scanning
 * @return int
 */
int VtFile_scan(struct VtFile *file_obj, const char *file_path);

/**
 * @brief Rescan a previously submitted file or schedule a scan to be performed in the future.
 *
 * @param file_obj File scan object
 * @param hash resouce to rescan
 * @param date default to 0, as not specified. If not specified, rescan immediately.
 * 		If specifed, it will be performed at the desired date.
 *      Private API permissions are required to specify this parameter
 * @param period  default 0, as not specified.   If specified period in days file
 *		to be rescaned. Private API permissions are required to specify this parameter
 * @param repeat default 0, as not specified.  If specified, file will be rescanned
 * every PERIOD paramater days, for REPEAT times.
 * @param notify_url default NULL, as not specified.  If specified, a POST will be sent to URL.
 *  Private API permissions are required to specify this parameter
 * @param notify_changes_only if notify_url set, only notify of changes
 * @return int
 */
int VtFile_rescanHash(struct VtFile *file_obj, const char *hash,
	time_t date, int period, int repeat, const char *notify_url, bool notify_changes_only);

/**
 * @brief Delete a scheduled rescan task
 *
 * @param file_obj VtFile object pointer
 * @param hash  resoruce to remove
 * @return int
 */

int VtFile_rescanDelete(struct VtFile *file_obj,
 const char *hash);

/**
 * @brief Fetch Report on a resource
 *
 * @param file_obj file object
 * @param resource  Hash, scan_id, or resource to fetch
 * @return int
 */
int VtFile_report(struct VtFile *file_obj, const char *resource);

struct VtResponse * VtFile_getResponse(struct VtFile *file_obj);


/**
 * @brief Search API
 *
 * @param file_obj file object
 * @param query Search query
 * @param cb Callback function pointer.  Will return hashes
 * @param user_data pointer to data pass to callback function.
 * @return int
 */
int VtFile_search(struct VtFile *file_obj, const char *query,
	void (*cb)(const char *resource, void *data),
	void *user_data);

#ifdef JANSSON_H



/**
 * @brief Get the clustering data
 * @brief Requires private-api permissions
 *
 * @param file_obj  File object
 * @param cluster_date   Clustering report date
 * @param cb write callback. will return a json_t object that you will need to parse
 * @param user_data user callback data
 * @return int.  0 for OK or error code
 */
int VtFile_clusters(struct VtFile *file_obj, const char *cluster_date,
	void (*cb)(json_t *cluster_json, void *data),
	void *user_data);
#endif


/**
 * @brief Download a file. callback function to write to memory, disk, network, etc
 * @brief Requires private-api permissions
 *
 * @param file_obj  File object
 * @param hash hash
 * @param cb write callback. Theis function will be called muliiple
 * @param user_data user callback data
 * @return int.  0 for OK or error code
 */
int VtFile_download(struct VtFile *file_obj, const char *hash,
	size_t (*cb)(char *ptr, size_t size, size_t nmemb, void *userdata), void *user_data);

/**
 * @brief Download and save to a file
 *
 * @param file_obj object
 * @param hash of file to download
 * @param out_file path to output file
 * @return int
 */
int VtFile_downloadToFile(struct VtFile *file_obj, const char *hash, const char *out_file);

/** @} */


#ifdef  __cplusplus
}
#endif /*cplusplus*/

#endif
