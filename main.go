package main

// #include <unistd.h>
// #include "loadsym.h"
// #cgo LDFLAGS: -ldl -lpthread
// #cgo CFLAGS: -D_GNU_SOURCE
import (
	"C"
)
import (
	"unsafe"
)

func main() {
	C.init_lib_wrapper(C.CString("Go"))
}

//export go_read
func go_read(s C.int, buf unsafe.Pointer, count C.size_t) C.ssize_t {
	C.init_lib_wrapper(C.CString("Go Read"))

	return C.true_read(s, buf, count)
}

//since we do not have const char* in go side, we use a c shimming layer.
//export go_write
func go_write(fd C.int, buf unsafe.Pointer, count C.size_t) C.ssize_t {
	C.init_lib_wrapper(C.CString("Go Write"))

	return C.true_write(fd, buf, count)

}
