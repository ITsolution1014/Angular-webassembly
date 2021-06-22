exports.cmd =
  emcc -Os src/app/wasm/3d-cube/soil/libSOIL.bc src/app/wasm/3d-cube/3d-cube.c++ -o src/assets/wasm/3d-cube.js -s LEGACY_GL_EMULATION=1 -I src/app/wasm/3d-cube/soil -I src/app/wasm/3d-cube/soil/opencv2/imgcodes/src -s EXTRA_EXPORTED_RUNTIME_METHODS=\"['ccall']\" -s FORCE_FILESYSTEM=1 -s MODULARIZE=1 -s EXPORT_NAME="Cube3dModule" -s LLD_REPORT_UNDEFINED;
