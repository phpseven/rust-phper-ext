// Copyright (c) 2019 jmjoy
// PHPER is licensed under Mulan PSL v2.
// You can use this software according to the terms and conditions of the Mulan
// PSL v2. You may obtain a copy of Mulan PSL v2 at:
//          http://license.coscl.org.cn/MulanPSL2
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY
// KIND, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
// See the Mulan PSL v2 for more details.

#include <stdbool.h>
#include <php.h>
#include <php_ini.h>
#include <ext/standard/info.h>
#include <zend_exceptions.h>
#include <main/SAPI.h>

typedef ZEND_INI_MH(phper_zend_ini_mh);

zend_string *zend_new_interned_string_(zend_string *str);
zend_class_entry phper_init_class_entry_ex(const char *class_name, size_t class_name_len, const zend_function_entry *functions);
zend_uchar phper_zval_get_type(const zval* pz);

zend_string *phper_zend_new_interned_string(zend_string *str) {
    return zend_new_interned_string(str);
}

zend_class_entry phper_init_class_entry_ex(const char *class_name, size_t class_name_len, const zend_function_entry *functions) {
    zend_class_entry class_container;
    INIT_CLASS_ENTRY_EX(class_container, class_name, class_name_len, functions);
    return class_container;
}

zend_uchar phper_zval_get_type(const zval* pz) {
    return zval_get_type(pz);
}

void phper_zval_arr(zval *val, zend_array *arr) {
    ZVAL_ARR(val, arr);
}

void phper_zval_new_arr(zval *val) {
#if PHP_VERSION_ID < 80100
    ZVAL_NEW_ARR(val);
#else
    array_init(val);
#endif
}

void phper_zval_stringl(zval *val, const char *s, size_t len) {
    ZVAL_STRINGL(val, s, len);
}

char *phper_z_strval_p(const zval *v) {
    return Z_STRVAL_P(v);
}

zval *phper_get_this(zend_execute_data *execute_data) {
    return getThis();
}

void phper_zval_zval(zval *val, zval *zv, int copy, int dtor) {
    ZVAL_ZVAL(val, zv, copy, dtor);
}

void phper_zval_copy(zval *val, const zval *zv) {
    ZVAL_COPY(val, zv);
}

void phper_zval_copy_value(zval *val, const zval *zv) {
    ZVAL_COPY_VALUE(val, zv);
}

zend_string *phper_zval_get_string(zval *op) {
    return zval_get_string(op);
}

zend_long phper_zval_get_long(zval *op) {
    return zval_get_long(op);
}

zend_string *phper_zend_string_init(const char *str, size_t len, int persistent) {
    return zend_string_init(str, len, persistent);
}

zend_string *phper_zend_string_alloc(size_t len, int persistent) {
    return zend_string_alloc(len, persistent);
}

void phper_zend_string_release(zend_string *s) {
    return zend_string_release(s);
}

zval* phper_zend_hash_str_update(HashTable *ht, const char *key, size_t len, zval *pData) {
    return zend_hash_str_update(ht, key, len, pData);
}

zval* phper_zend_hash_index_update(HashTable *ht, zend_ulong h, zval *pData) {
    return zend_hash_index_update(ht, h, pData);
}

zval* phper_zend_hash_next_index_insert(HashTable *ht, zval *pData) {
    return zend_hash_next_index_insert(ht, pData);
}

void phper_array_init(zval *arg) {
    array_init(arg);
}

void *phper_zend_hash_str_find_ptr(const HashTable *ht, const char *str, size_t len) {
    return zend_hash_str_find_ptr(ht, str, len);
}

void phper_zval_obj(zval *z, zend_object *o) {
    ZVAL_OBJ(z, o);
}

void phper_zval_func(zval *z, zend_function *f) {
    ZVAL_FUNC(z, f);
}

#if PHP_VERSION_ID < 80000
static zend_string *phper_zend_string_concat3(
        const char *str1, size_t str1_len,
        const char *str2, size_t str2_len,
        const char *str3, size_t str3_len)
{
    size_t len = str1_len + str2_len + str3_len;
    zend_string *res = zend_string_alloc(len, 0);

    memcpy(ZSTR_VAL(res), str1, str1_len);
    memcpy(ZSTR_VAL(res) + str1_len, str2, str2_len);
    memcpy(ZSTR_VAL(res) + str1_len + str2_len, str3, str3_len);
    ZSTR_VAL(res)[len] = '\0';

    return res;
}
#endif

zend_string *phper_get_function_or_method_name(const zend_function *func) {
    #if PHP_VERSION_ID >= 80000
    return get_function_or_method_name(func);
    #else
    if (func->common.scope) {
        return phper_zend_string_concat3(
                ZSTR_VAL(func->common.scope->name), ZSTR_LEN(func->common.scope->name),
                "::", sizeof("::") - 1,
                ZSTR_VAL(func->common.function_name), ZSTR_LEN(func->common.function_name));
    }
    return func->common.function_name ? zend_string_copy(func->common.function_name) : zend_string_init("main", sizeof("main") - 1, 0);
    #endif
}

void phper_zval_ptr_dtor(zval *zv) {
    ZVAL_PTR_DTOR(zv);
}

size_t phper_zend_object_properties_size(zend_class_entry *ce) {
    return zend_object_properties_size(ce);
}

void *phper_zend_object_alloc(size_t obj_size, zend_class_entry *ce) {
    #if PHP_VERSION_ID >= 70300
    return zend_object_alloc(obj_size, ce);
    #else
    void *obj = emalloc(obj_size + zend_object_properties_size(ce));
    memset(obj, 0, obj_size - sizeof(zval));
    return obj;
    #endif
}

zend_object* (**phper_get_create_object(zend_class_entry *ce))(zend_class_entry *class_type) {
    return &ce->create_object;
}

bool phper_object_init_ex(zval *arg, zend_class_entry *class_type) {
    return object_init_ex(arg, class_type) == SUCCESS;
}

bool phper_call_user_function(HashTable *function_table, zval *object, zval *function_name, zval *retval_ptr, uint32_t param_count, zval params[]) {
    function_table = function_table;
    return call_user_function(function_table, object, function_name, retval_ptr, param_count, params) == SUCCESS;
}

bool phper_zend_hash_str_exists(const HashTable *ht, const char *str, size_t len) {
    return zend_hash_str_exists(ht, str, len) != 0;
}

bool phper_zend_hash_index_exists(const HashTable *ht, zend_ulong h) {
    return zend_hash_index_exists(ht, h) != 0;
}

void phper_zval_ptr_dtor_nogc(zval *zval_ptr) {
    zval_ptr_dtor_nogc(zval_ptr);
}

bool phper_z_refcounted_p(zval *zval_ptr) {
    return Z_REFCOUNTED_P(zval_ptr);
}

zval *phper_execute_data_call_arg(zend_execute_data *execute_data, int index) {
    return ZEND_CALL_ARG(execute_data, index);
}

int phper_z_res_handle_p(const zval *val) {
    return Z_RES_HANDLE_P(val);
}

int phper_zstr_len(const zend_string *s) {
    return ZSTR_LEN(s);
}

const char *phper_zstr_val(const zend_string *s) {
    return ZSTR_VAL(s);
}

void *phper_emalloc(size_t size) {
    return emalloc(size);
}

void phper_efree(void *ptr) {
    return efree(ptr);
}

void phper_separate_string(zval *zv) {
    SEPARATE_STRING(zv);
}

void phper_separate_array(zval *zv) {
    SEPARATE_ARRAY(zv);
}

void phper_zval_null(zval *zv) {
    ZVAL_NULL(zv);
}

void phper_zval_true(zval *zv) {
    ZVAL_TRUE(zv);
}

void phper_zval_false(zval *zv) {
    ZVAL_FALSE(zv);
}

void phper_zval_long(zval *zv, zend_long l) {
    ZVAL_LONG(zv, l);
}

void phper_zval_double(zval *zv, double d) {
    ZVAL_DOUBLE(zv, d);
}

int phper_z_type_info_p(zval *zv) {
    return Z_TYPE_INFO_P(zv);
}

int phper_z_type_p(zval *zv) {
    return Z_TYPE_P(zv);
}

void phper_zval_str(zval *zv, zend_string *s) {
    ZVAL_STR(zv, s);
}

zend_array *phper_zend_new_array(uint32_t nSize) {
    return zend_new_array(nSize);
}
