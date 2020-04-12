function doit() {
    const mainloop = Module.cwrap('mainloop', null, ['void']);
    requestAnimationFrame(function () {
        mainloop();
        doit();
    });
}


Module.postRun = [doit];