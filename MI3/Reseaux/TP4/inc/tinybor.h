/* bor-util.h : Boite a Outil Reseau
 *
 * Edouard.Thiel@lif.univ-mrs.fr - 29/05/2011 - V 2.0
 *
 * This program is free software under the terms of the
 * GNU Lesser General Public License (LGPL) version 2.1.
*/

#include <signal.h>     /* sigaction */
#include <sys/wait.h>   /* wait */
#include <sys/stat.h>   /* open */
#include <fcntl.h>      /* open */


int bor_signal (int, void (*h)(int), int);
