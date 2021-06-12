#ifndef __SET_CPP_H__
#define __SET_CPP_H__

#ifdef __cplusplus

extern "C" void pascal_set_construct(SetArrayElemType* set_array,
                     size_t set_card,
                     int param1,
                     va_list params);

template<int n>
class set_template {
  public:
    SetArrayElemType setarray[(n + BITS_PER_WORD - 1) / BITS_PER_WORD];

    static set_template of(int param1, ...) {
    set_template s;
    va_list ap;
    va_start(ap, param1);
    pascal_set_construct(s.setarray, items(s.setarray), param1, ap);
    va_end(ap);
    return s;
    }
    set_template operator +(set_template const& s) const {
    set_template result;
    for(size_t i = 0; i < items(setarray); i++) {
        result.setarray[i] = setarray[i] | s.setarray[i];
    }
    return result;
    }
    set_template operator *(set_template const& s) const {
    set_template result;
    for(size_t i = 0; i < items(setarray); i++) {
        result.setarray[i] = setarray[i] & s.setarray[i];
    }
    return result;
    }
    set_template operator -(set_template const& s) const {
    set_template result;
    for(size_t i = 0; i < items(setarray); i++) {
        result.setarray[i] = setarray[i] & ~s.setarray[i];
    }
    return result;
    }

    boolean operator <=(set_template const& s) const {
    for(size_t i = 0; i < items(setarray); i++) {
        if (setarray[i] & ~s.setarray[i]) return false;
    }
    return true;
    }
    boolean operator >=(set_template const& s) const {
    for(size_t i = 0; i < items(setarray); i++) {
        if (s.setarray[i] & ~setarray[i]) return false;
    }
    return true;
    }
    boolean operator ==(set_template const& s) const {
    for(size_t i = 0; i < items(setarray); i++) {
        if (s.setarray[i] != setarray[i]) return false;
    }
    return true;
    }
    boolean operator !=(set_template const& s) const {
    for(size_t i = 0; i < items(setarray); i++) {
        if (s.setarray[i] != setarray[i]) return true;
    }
    return false;
    }
    boolean has(SetElemType elem) const {
    return (setarray[(unsigned)elem / BITS_PER_WORD] &
           (SetArrayElemType(1) << ((unsigned)elem % BITS_PER_WORD))) != 0;
    }
};

typedef set_template<MAX_SET_CARD> set;
#endif//CPP

#endif
