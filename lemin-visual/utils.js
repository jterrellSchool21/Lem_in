
function returnMaxAndMinArrayValues(arr) {
    let resultArr = [];
    let xArr = [];
    let yArr = [];
    arr.forEach(function(room) {
        xArr.push(parseInt(room.x));
        yArr.push(parseInt(room.y));
    })
    let maxX = Math.max.apply(null, xArr);
    let maxY = Math.max.apply(null, yArr);
    let minX = Math.min.apply(null, xArr);
    let minY = Math.min.apply(null, yArr);
    resultArr.maxx = maxX;
    resultArr.maxy = maxY;
    resultArr.minx = minX;
    resultArr.miny = minY;
    return resultArr;
}

function is_too_big(arr) {

    let isOverlap = arr.some(function(room) {
        if (room['x'] * roomSize > screenWidth + roomSize)
            return true;
        else if (room['y'] * roomSize > screenHeight + roomSize)
            return true;
        else
            return false;
    })
    if (isOverlap === true) {
        let maxAndMinRoomValues;

        maxAndMinRoomValues = returnMaxAndMinArrayValues(arr);
        let maxX = maxAndMinRoomValues.maxx;
        let maxY = maxAndMinRoomValues.maxy;
        let delimY = 0;
        let delimX = 0;


        while (maxX > parseInt(screenWidth) / roomSize) {
            maxX /= 10;
            delimX++;
        }
        while (maxY > parseInt(screenHeight) / roomSize) {
            maxY /= 10;
            delimY++;
        }
        if (delimX > 1 || delimY > 1) {

            let maxDelim = delimX >= delimY ? delimX + 1 : delimY + 1;
            arr = arr.map(function(room) {
                room['x'] = Math.floor(parseInt(room['x']) / (maxDelim * 10));
                room['y'] = Math.floor(parseInt(room['y']) / (maxDelim * 10));
                return room;

            });
        }
    }
    return arr;
}

function is_overlap(arr) {
    let isOverlap = arr.some(function(room) {
        if (room['x'] * roomSize > screenWidth + roomSize)
            return true;
        else if (room['y'] * roomSize > screenHeight + roomSize)
            return true;
        else
            return false;
    })
    let maxAndMinRoomValues = returnMaxAndMinArrayValues(arr);
    let bestScreenWidth = maxAndMinRoomValues.maxx * (roomSize + 2);
    let bestScreenHeight = maxAndMinRoomValues.maxy * (roomSize + 2);
    if (isOverlap === true) {

        if (bestScreenWidth > screenWidth) {
            screenWidth = bestScreenWidth;
            container.style.width = screenWidth;
        }
        if (bestScreenHeight > screenHeight) {
            screenHeight = bestScreenHeight;
            container.style.height = screenHeight;
        }
    }
}

function changeInfo(info) {
    let maxAndMinRoomValues;

    maxAndMinRoomValues = returnMaxAndMinArrayValues(info['rooms']);
    info['rooms'] = info['rooms'].map(function(room) {
        room['x'] = Math.floor(parseInt(room['x']) - maxAndMinRoomValues.minx + 1);
        room['y'] = Math.floor(parseInt(room['y']) - maxAndMinRoomValues.miny + 1);
        return room;
    });
    is_too_big(info['rooms']);
    is_overlap(info['rooms']);

    return info;
}

function fillInfo(info) {
    let ants = document.getElementById('quant_ants');
    let roomList = document.getElementById('rooms-list');
    let roomsConnections = document.getElementById('rooms-connections');
    let antsPaths = document.getElementById('ants-paths');
    ants.innerHTML = '<b class="inner-info-header">Ants:</b><div class="inner-info">' + info['quant_of_ants'] + '</div>';

    let generatedRooms = info['rooms'].reduce(function (string, curr) {
        if (!string.length)
            return info['rooms'][0]['name'] + ', ' + curr['name'];
        return string + ', ' + curr['name']
    });
    roomList.innerHTML = '<b class="inner-info-header">Rooms:</b><br><div class="inner-info">' + generatedRooms + '</div>';


    let generatedConn = info['rooms'].reduce(function (string, curr) {
        if (!string.length) {
            let currConnections;
            if(info['rooms'][0]['connections'] !== null && info['rooms'][0]['connections'].length)
            {
                currConnections = info['rooms'][0]['connections'].reduce(function (connectionsString, currConn) {
                    if (connectionsString !== undefined && !connectionsString.length)
                    {
                        if (curr['connections'][0] != null)
                            return curr['connections'][0];
                        else
                            return "";
                    }
                    if (!currConn)
                        return connectionsString;
                    return connectionsString + ', ' + currConn;
                });
            }
            else
                currConnections = "";
            let connForFirstRoom;
            if (curr['connections'] !== undefined && curr['connections'].length) {
                connForFirstRoom = curr['name'] + ' :' + curr['connections'].reduce(function (connectionString, currConn) {
                    if (connectionString !== undefined && !connectionString.length)
                        return curr['connections'][0];
                    if (!currConn)
                        return connectionString;
                    return connectionString + ', ' + currConn;
                }) + '\n';
            } else
                connForFirstRoom = '<b>'+curr['name']+'</b>' + ' :' + "no connections<br>";
            return '<b>' + info['rooms'][0]['name'] + '</b>' + ': ' + currConnections + '<br>' + connForFirstRoom;
        } else {
            if (curr['connections'] !== undefined && curr['connections'].length) {
                let currConnections = curr['connections'].reduce(function (connectionsString, currConn) {
                    if (connectionsString !== undefined && !connectionsString.length)
                        return curr['connections'][0];
                    return connectionsString + ', ' + currConn;
                });
                return string + ('<b>'+curr['name']+'</b>' + ': ' + currConnections + '<br>');
            } else
                return string + ('<b>'+curr['name']+'</b>' + ': ' + 'no connections' + '<br>');
        }

    })
    roomsConnections.innerHTML = '<b>Rooms connections:\n</b><div class="inner-info">' + generatedConn + '</div>';
    if(info['ants'])
    {
        let generatedPaths = info['ants'].reduce(function (string, curr, index) {
            let firstString;
            if (!string.length) {
                if(info['ants'][0]['path'] != null && info['ants'][0]['path'].length)
                {
                    firstString = '<b>L1: </b>' + info['ants'][0]['path'].reduce(function (connectionsString, currConn) {
                        if (!connectionsString.length)
                            return info['ants'][0]['path'][0];
                        if (!currConn)
                            return connectionsString;
                        return connectionsString + '--> ' + currConn;
                    }) + '<br>';
                }
                else
                    firstString = '<b>L1: </b>no path' + '<br>';
            }
            let currConnections;
            if(curr['path'])
            {
                currConnections = curr['path'].reduce(function (connectionsString, currConn, index) {
                    if (!connectionsString) {
                        if (curr['path'][index])
                            return curr['path'][index];
                        else
                            return connectionsString;
                    }
                    if (currConn) {
                        if (connectionsString.length)
                            return connectionsString + '--> ' + currConn;
                        else return currConn;
                    } else
                        return connectionsString
                });
            }
            else
                currConnections ='no path';
            if (index === 1)
                return firstString + ('<b>L' + curr['number'] + ': </b>' + currConnections + '<br>');
            return string + ('<b>L' + curr['number'] + ': </b>' + currConnections + '<br>');
        })

        antsPaths.innerHTML = '<b class="inner-info-header">Ants paths:\n</b><div class="inner-info">' + generatedPaths +'</div>';
    }
}
