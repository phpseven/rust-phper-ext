// Copyright (c) 2019 jmjoy
// PHPER is licensed under Mulan PSL v2.
// You can use this software according to the terms and conditions of the Mulan
// PSL v2. You may obtain a copy of Mulan PSL v2 at:
//          http://license.coscl.org.cn/MulanPSL2
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY
// KIND, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
// See the Mulan PSL v2 for more details.

use phper_sys::*;

fn main() {
    phper_build::register_configures();
    assert_eq!(
        PHP_DEBUG, 0,
        "PHPER not support DEBUG mode now (php built with `--enable-debug`)."
    );
    assert_eq!(
        USING_ZTS, 0,
        "PHPER not support ZTS mode now (php built with `--enable-maintainer-zts` or \
         `--enable-zts`)."
    );
}
