#ifndef __VARING_STRING_H__
#define __VARING_STRING_H__

#ifdef __cplusplus

#define BETWEEN(down, value, up) (unsigned(value) - down <= unsigned(up - down))
#define noconst

#ifndef MAX_STRING_SIZE
#define MAX_STRING_SIZE 255
#endif

class varying_string_header
{
protected:
    unsigned int  len;

public:
    char *get_body() const
    {
        return (char *)(&len + 1);
    }

    friend int length(const varying_string_header &str)
    {
        return str.len;
    }
    int length() const
    {
        return len;
    }
    friend void set_length(varying_string_header &str, int new_length)
    {
        str.len = new_length;
    }
    void set_length(int new_length)
    {
        len = new_length;
    }
    void to_array(char *dst_buf, size_t dst_buf_size) const
    {
        size_t size = length();
        if (size > dst_buf_size)
        {
            size = dst_buf_size;
        }
        memcpy(dst_buf, get_body(), size);
        if (size < dst_buf_size)
        {
            dst_buf[size] = '\0';
        }
    }

    char &operator*()
    {
        return *get_body();
    }

    int compare(const char *str) const
    {
        size_t right_len = strlen(str);
        size_t left_len = length();
        size_t min_len = left_len < right_len ? left_len : right_len;
        int diff = memcmp(get_body(), str, min_len);
        return diff == 0 ? left_len - right_len : diff;
    }
    int compare(const varying_string_header &str) const
    {
        size_t left_len = length();
        size_t right_len = str.length();
        size_t min_len = left_len < right_len ? left_len : right_len;
        int diff = memcmp(get_body(), str.get_body(), min_len);
        return diff == 0 ? left_len - right_len : diff;
    }
    int compare(char ch) const
    {
        unsigned len = length();
        return len == 0 ? -(unsigned char)ch : ch == *get_body()
               ? len - 1
               : (unsigned char)ch - (unsigned char) * get_body();
    }

    boolean operator >  (const varying_string_header &str) const
    {
        return compare(str) > 0;
    }
    boolean operator >= (const varying_string_header &str) const
    {
        return compare(str) >= 0;
    }
    boolean operator < (const varying_string_header &str) const
    {
        return compare(str) < 0;
    }
    boolean operator <= (const varying_string_header &str) const
    {
        return compare(str) <= 0;
    }
    boolean operator == (const varying_string_header &str) const
    {
        return compare(str) == 0;
    }
    boolean operator != (const varying_string_header &str) const
    {
        return compare(str) != 0;
    }

    boolean operator >  (const char *ptr) const
    {
        return compare(ptr) > 0;
    }
    boolean operator >= (const char *ptr) const
    {
        return compare(ptr) >= 0;
    }
    boolean operator < (const char *ptr) const
    {
        return compare(ptr) < 0;
    }
    boolean operator <= (const char *ptr) const
    {
        return compare(ptr) <= 0;
    }
    boolean operator == (const char *ptr) const
    {
        return compare(ptr) == 0;
    }
    boolean operator != (const char *ptr) const
    {
        return compare(ptr) != 0;
    }

    boolean operator >  (char ch) const
    {
        return compare(ch) > 0;
    }
    boolean operator >= (char ch) const
    {
        return compare(ch) >= 0;
    }
    boolean operator < (char ch) const
    {
        return compare(ch) < 0;
    }
    boolean operator <= (char ch) const
    {
        return compare(ch) <= 0;
    }
    boolean operator == (char ch) const
    {
        return compare(ch) == 0;
    }
    boolean operator != (char ch) const
    {
        return compare(ch) != 0;
    }

    friend text &operator << (text &t, varying_string_header const &str)
    {
        pio_output_string((text_descriptor *)&t, str.get_body(),
                          str.length(), NULL);
        return t;
    }

    friend format_varying_string format(varying_string_header const &str,
                                        int width)
    {
        return format_varying_string(str.get_body(), str.length(), width);
    }
};


template<size_t max_size>
class varying_string : public varying_string_header
{
public:
    char body[max_size];
    typedef varying_string<MAX_STRING_SIZE> string;

#define STRING_FETCH_OPERATOR(index_type, modifier) \
    char modifier& operator[](index_type index) modifier { \
  assert(size_t(index) <= max_size); \
  return body[index-1]; \
    }
    STRING_FETCH_OPERATOR(char, noconst);
    STRING_FETCH_OPERATOR(char, const);
    STRING_FETCH_OPERATOR(unsigned char, noconst);
    STRING_FETCH_OPERATOR(unsigned char, const);
    STRING_FETCH_OPERATOR(short, noconst);
    STRING_FETCH_OPERATOR(short, const);
    STRING_FETCH_OPERATOR(unsigned short, noconst);
    STRING_FETCH_OPERATOR(unsigned short, const);
    STRING_FETCH_OPERATOR(int, noconst);
    STRING_FETCH_OPERATOR(int, const);
    STRING_FETCH_OPERATOR(unsigned, noconst);
    STRING_FETCH_OPERATOR(unsigned, const);
#undef STRING_FETCH_OPERTATOR

    operator char const *() const
    {
        size_t len = length();
        if (len < max_size)
        {
            *((char *)body + len) = '\0';
            return body;
        }
        else
        {
            //return lpsz(1, len, body);//LosPhoenix
            return NULL;
        }
    }

    friend text &operator >> (text &t, varying_string &str)
    {
        str.set_length(pio_input_string((text_descriptor *)&t, str.get_body(),
                                        max_size, false));
        return t;
    }

    void operator = (const char *str)
    {
        size_t len = strlen(str);
        if (len > max_size) len = max_size;
        memcpy(body, str, len);
        set_length(len);
    }
    void operator = (char elem)
    {
        body[0] = elem;
        set_length(1);
    }
    void operator = (const varying_string_header &str)
    {
        size_t len = str.length();
        if (len > max_size) len = max_size;
        memcpy(body, str.get_body(), len);
        set_length(len);
    }

    void operator = (const varying_string &str)
    {
        size_t len = str.length();
        if (len > max_size) len = max_size;
        memcpy(body, str.get_body(), len);
        set_length(len);
    }

    string operator + (const varying_string_header &str) const;

    string operator + (const char *str) const;

    string operator + (char ch) const;

    string operator + (unsigned char ch) const;

    string operator + (new_line_marker &) const;

    varying_string(const varying_string_header &str)
    {
        size_t len = str.length();
        if (len > max_size) len = max_size;
        memcpy(body, str.get_body(), len);
        set_length(len);
    }
    varying_string(const char *str)
    {
        size_t len = strlen(str);
        if (len > max_size) len = max_size;
        memcpy(body, str, len);
        set_length(len);
    }
    varying_string(char ch)
    {
        if (max_size >= 1)
        {
            set_length(1);
            body[0] = ch;
        }
    }
    varying_string()
    {
        set_length(0);
    }
};

typedef varying_string<MAX_STRING_SIZE> string;


template<size_t max_size>
inline string varying_string<max_size>::operator +
(const varying_string_header &str) const
{
    string result;
    size_t left_len = length();
    size_t right_len = str.length();
    memcpy(&result.body, body, left_len);
    size_t append_len = MAX_STRING_SIZE - left_len < right_len
                        ? MAX_STRING_SIZE - left_len : right_len;
    memcpy(&result.body[left_len], str.get_body(), append_len);
    result.set_length(left_len + append_len);
    return result;
}

template<size_t max_size>
inline string varying_string<max_size>::operator + (const char *str) const
{
    string result;
    size_t left_len = length();
    size_t right_len = strlen(str);
    memcpy(result.body, body, left_len);
    size_t append_len = MAX_STRING_SIZE - left_len < right_len
                        ? MAX_STRING_SIZE - left_len : right_len;
    memcpy(&result.body[left_len], str, append_len);
    result.set_length(left_len + append_len);
    return result;
}

template<size_t max_size>
inline string varying_string<max_size>::operator + (char ch) const
{
    string result;
    size_t len = length();
    memcpy(result.body, body, len);
    if (len < MAX_STRING_SIZE)
    {
        result.body[len] = ch;
        result.set_length(len + 1);
    }
    else
    {
        result.set_length(len);
    }
    return result;
}

template<size_t max_size>
inline string varying_string<max_size>::operator + (unsigned char ch) const
{
    string result;
    size_t len = length();
    memcpy(result.body, body, len);
    if (len < MAX_STRING_SIZE)
    {
        result.body[len] = ch;
        result.set_length(len + 1);
    }
    else
    {
        result.set_length(len);
    }
    return result;
}

template<size_t max_size>
inline string varying_string<max_size>::operator + (new_line_marker &) const
{
    string result;
    size_t len = length();
    memcpy(result.body, body, len);
    if (len < MAX_STRING_SIZE)
    {
        result.body[len] = '\n';
        result.set_length(len + 1);
    }
    else
    {
        result.set_length(len);
    }
    return result;
}


template<size_t max_size>
inline void str(int val, varying_string<max_size> &s)
{
    s.set_length(sprintf(s.body, "%d", val));
}

template<size_t max_size>
inline void str(long val, varying_string<max_size> &s)
{
    s.set_length(sprintf(s.body, "%ld", val));
}

template<size_t max_size>
inline void str(unsigned val, varying_string<max_size> &s)
{
    s.set_length(sprintf(s.body, "%u", val));
}

template<size_t max_size>
inline void str(unsigned long val, varying_string<max_size> &s)
{
    s.set_length(sprintf(s.body, "%lu", val));
}

template<size_t max_size>
inline void str(int val, int width, varying_string<max_size> &s)
{
    s.set_length(sprintf(s.body, "%*d", width, val));
}

template<size_t max_size>
inline void str(unsigned val, int width, varying_string<max_size> &s)
{
    s.set_length(sprintf(s.body, "%*u", width, val));
}

template<size_t max_size>
inline void str(long val, int width, varying_string<max_size> &s)
{
    s.set_length(sprintf(s.body, "%*ld", width, val));
}

template<size_t max_size>
inline void str(unsigned long val, int width, varying_string<max_size> &s)
{
    s.set_length(sprintf(s.body, "%*lu", width, val));
}

template<size_t max_size>
inline void str(double val, varying_string<max_size> &s)
{
    s.set_length(sprintf(s.body, "% G", val));
}

template<size_t max_size>
inline void str(double val, int width, varying_string<max_size> &s)
{
    s.set_length(sprintf(s.body, "%*E", width, val));
}

template<size_t max_size>
inline void str(double val, int width, int prec, varying_string<max_size> &s)
{
    s.set_length(sprintf(s.body, "%*.*f", width, prec, val));
}

inline string copy(varying_string_header const &str, int p, int n)
{
    string result;
    size_t len = str.length();
    result.set_length(0);
    if (size_t(p - 1) < len)
    {
        size_t count = size_t(p - 1 + n) <= len ? size_t(n) : len - p + 1;
        memcpy(result.body, str.get_body() + p - 1, count);
        result.set_length(count);
    }
    return result;
}

inline string copy(char const *str, int p, int n)
{
    string result;
    size_t len = strlen(str);
    result.set_length(len);
    if (size_t(p - 1) < len)
    {
        size_t count = size_t(p + n) <= len ? size_t(n) : len - p + 1;
        memcpy(result.body, str + p - 1, count);
        result.set_length(count);
    }
    return result;
}

template<size_t max_size>
inline void insert(string const             &ins,
                   varying_string<max_size> &str,
                   int                       pos)
{
    size_t len = str.length();
    size_t inslen = ins.length();
    assert(pos > 0 && pos <= len + 1 && size_t(inslen + len) < sizeof str);
    char *dst = str.get_body();
    memmove(dst + pos - 1 + inslen, dst + pos - 1, len - pos + 1);
    memcpy(dst + pos - 1, ins.body, inslen);
    str.set_length(len + inslen);
}

inline int pos(string const &q, string const &z)
{
    int   q_len = q.length();
    int   z_len = z.length();
    char *q_ptr = q.get_body();
    char *z_ptr = z.get_body();
    int pos = 0;
    while (z_len - pos >= q_len)
    {
        int i;
        for (i = 0; i < q_len && z_ptr[pos + i] == q_ptr[i]; i++);
        if (i == q_len)
        {
            return pos + 1;
        }
        pos += 1;
    }
    return 0;
}

template<size_t max_size>
inline void Delete(varying_string<max_size> &s, int index, int count)
{
    int len = s.length();
    assert(index > 0 && count >= 0);
    if (index + count > len)
    {
        count = len - index + 1;
    }
    char *str = s.get_body();
    memcpy(str + index - 1, str + index - 1 + count, len - index - count + 1);
    s.set_length(len - count);
}

inline void val(string const &str, int &val, int &c)
{
    int x, n;
    if (sscanf(str.body, "%d%n", &x, &n) == 1)
    {
        val = x;
        c = (n == str.length()) ? 0 : n + 1;
    }
    else
    {
        c = 1;
    }
}

inline void val(string const &str, real &val, int &c)
{
    double x;
    int    n;
    if (sscanf(str.body, "%lf%n", &x, &n) == 1)
    {
        val = (real)x;
        c = (n == str.length()) ? 0 : n + 1;
    }
    else
    {
        c = 1;
    }
}

#endif/*CPP*/
#endif/*ARRAY_H*/
