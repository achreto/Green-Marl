#ifndef GM_H_
#define GM_H_
#include <math.h>
#include <stdlib.h>

//------------------------------------------------------------
// This is the root header for external applications.
// This header includes all the 'modules' in gm_graph lib
//------------------------------------------------------------
#include "gm_internal.h"

#include "gm_graph_typedef.h"
#include "gm_graph.h"
#include "gm_runtime.h"
#include "gm_atomic_wrapper.h"
#include "gm_atomic_operations.h"
#include "gm_lock.h"
#include "gm_bitmap.h"
#include "gm_mem_helper.h"

#include "gm_bfs_template.h"
#include "gm_dfs_template.h"
#include "gm_common_neighbor_iter.h"

#include "gm_set.h"
#include "gm_seq.h"
#include "gm_order.h"
#include "gm_collection.h"
#include "gm_map.h"
#include "gm_mutatable_priority_map.h"

#include "gm_useropt.h"
#include "gm_default_usermain.h"



#define CONFIG_SHM_FILE_NAME "/tmp/alloctest-bench"

#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <unistd.h>

extern struct timeval ___t_start;

static inline void gm_rt_signal_ready(void)
{
    fprintf (stderr,"signalling readyness to %s\n", CONFIG_SHM_FILE_NAME ".ready");      
    FILE *fd2 = fopen(CONFIG_SHM_FILE_NAME ".ready", "w");
    if (fd2 == NULL) {
        fprintf (stderr, "ERROR: could not create the shared memory file descriptor\n");
    }

    usleep(250);
    gettimeofday(&___t_start, NULL);
}

static inline void gm_rt_signal_done(void)
{
    struct timeval ___t_end;
    gettimeofday(&___t_end, NULL);

    fprintf (stderr,"signalling done to %s\n", CONFIG_SHM_FILE_NAME ".done");      
    FILE *fd2 = fopen(CONFIG_SHM_FILE_NAME ".done", "w");
    if (fd2 == NULL) {
        fprintf (stderr, "ERROR: could not create the shared memory file descriptor\n");
    }

    fprintf (stderr,"benchmark took %lu seconds\n", ___t_end.tv_sec - ___t_start.tv_sec);

    usleep(250);
}


#endif  // GM_H_
