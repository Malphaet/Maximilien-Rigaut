/* bor-util.c : Boite a Outil Reseau
 *
 * Edouard.Thiel@lif.univ-mrs.fr - 22/01/2009 - V 2.0
 *
 * This program is free software under the terms of the
 * GNU Lesser General Public License (LGPL) version 2.1.
*/

int bor_signal (int sig, void (*h)(int), int options){
    int r;
    struct sigaction s;
    s.sa_handler = h;
    sigemptyset (&s.sa_mask);
    s.sa_flags = options;
    r = sigaction (sig, &s, NULL);
    if (r < 0) ERROR("Signal handling");
    return r;
}
