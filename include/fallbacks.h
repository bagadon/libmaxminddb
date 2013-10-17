#ifndef FALLBACKS_H
#define FALLBACKS_H

/* All of these functions were copied from the libiberty code base, which is
 * LPGPL 2+ */

/* *INDENT-OFF* */
#if !HAVE_MEMMEM
void *
memmem (const void *haystack, size_t haystack_len, const void *needle,
        size_t needle_len)
{
  const char *begin;
  const char *const last_possible
    = (const char *) haystack + haystack_len - needle_len;

  if (needle_len == 0)
    /* The first occurrence of the empty string is deemed to occur at
       the beginning of the string.  */
    return (void *) haystack;

  /* Sanity check, otherwise the loop might search through the whole
     memory.  */
  if (__builtin_expect (haystack_len < needle_len, 0))
    return NULL;

  for (begin = (const char *) haystack; begin <= last_possible; ++begin)
    if (begin[0] == ((const char *) needle)[0] &&
        !memcmp ((const void *) &begin[1],
                 (const void *) ((const char *) needle + 1),
                 needle_len - 1))
      return (void *) begin;

  return NULL;
}
#endif

#if !HAVE_STRDUP
char *
strdup(const char *s)
{
  size_t len = strlen (s) + 1;
  char *result = (char*) malloc (len);
  if (result == (char*) 0)
    return (char*) 0;
  return (char*) memcpy (result, s, len);
}
#endif

#if !HAVE_STRNDUP
char *strndup (const char *s, size_t n)
{
  char *result;
  size_t len = strlen (s);

  if (n < len)
    len = n;

  result = (char *) malloc (len + 1);
  if (!result)
    return 0;

  result[len] = '\0';
  return (char *) memcpy (result, s, len);
}
#endif

#endif                          /* FALLBACKS_H */
