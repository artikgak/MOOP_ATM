import QtQuick 2.0

Loader {
    id: loader
    source: ":/images/loader.gif"
    asynchronous: true
    visible: status == Loader.Ready
    onStatusChanged: if (loader.status == Loader.Ready) console.log('Loaded')
}
