#ifndef __SET_H__
#define __SET_H__

#define MAX_SET_CARD  256

#define eos              (MAX_SET_CARD)   /* end of set marker */
#define INTERVAL_MARKER  (MAX_SET_CARD+1) /* interval marker */

#define range(a,b) (a), INTERVAL_MARKER, (b)

typedef unsigned char SetElemType;
typedef integer       SetArrayElemType;

#define BITS_PER_WORD (sizeof(SetArrayElemType)*8)
#define ALL_BITS_SET  ((SetArrayElemType)-1)

#define set_of_enum(e) set_template<last_##e>

#ifndef __cplusplus /* language C */

#define SET_LENGTH (MAX_SET_CARD/BITS_PER_WORD)

typedef struct {
    SetArrayElemType setarray[SET_LENGTH];
} set;

boolean subset(set a, set b);    /* if <a> is subset of <b> */
boolean inset(SetElemType elem, set s);
boolean equivalent(set a, set b);
set     setof(int elem1, ...);
set     join(set a, set b);
set     difference(set a, set b);
set     intersect(set a, set b);

typedef unsigned int   set32;
typedef unsigned short set16;

#define ELEM(e)         (1L << (e))
#define INSET(e,s)      ((ELEM(e) & (s)) != 0)
#define DIFFERENCE(a,b) ((a) & ~(b))
#define    JOIN(a,b)       ((a) | (b))
#define INTERSECT(a,b)  ((a) & (b))
#define SUBSET(a,b)     (((a) & ~(b)) == 0)
#define EQUIVALENT(a,b) ((a) == (b))

#define RANGE(a,b)      (ELEM((a)+1) - ELEM(b))


#endif /* language C */


#endif
