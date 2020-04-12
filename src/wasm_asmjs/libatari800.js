function doit() {
    const mainloop = Module.cwrap('mainloop', null, ['void']);
    requestAnimationFrame(function () {
        mainloop();
        doit();
    });
}

function prepScreen() {
    const toHide = ["#output", "a", "#status", "#controls"];
    toHide.forEach(i => document.querySelector(i).style.display = "none");
}

function resize() {
    const canvas = document.querySelector("canvas");
    const canvasRatio = canvas.height / canvas.width;
    const windowRatio = window.innerHeight / window.innerWidth;
    let width;
    let height;

    if (windowRatio < canvasRatio) {
        height = window.innerHeight;
        width = height / canvasRatio;
    } else {
        width = window.innerWidth;
        height = width * canvasRatio;
    }

    canvas.style.width = `${width}px`;
    canvas.style.height = `${height}px`;
};

window.addEventListener('resize', resize, false);

Module.postRun = [doit, prepScreen, resize];