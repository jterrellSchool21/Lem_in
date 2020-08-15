
function Room(str, opt) {
    let splited = str.split(' ');
    this.name = splited[0];
    if(!opt)
        this.type = null;
    else
        this.type = opt;
    this.x = splited[1];
    this.y = splited[2];

    this.connections = [];
    this.toArr = function () {
        let arr = [];
        arr['name'] = this.name;
        arr['x'] = this.x;
        arr['y'] = this.y;
        arr['connections'] = this.connections;
        return arr;
    }
    this.createConn = function (nameOfRoom) {
        this.connections.push(nameOfRoom)
    }
    return this;
}

function checkPathForAnt(arr, number) {
    let antsInStr = [];
    let length = arr.length;
    arr.forEach(function (part) {
        let ant = part.split('-')[0];
        antsInStr.push(ant);
    })
    return antsInStr.indexOf('L' + toString(number));
}

function Ant(number, info) {
    this.number = number;
    let path = [];

    info.forEach(function (str) {
        let splited = str.split(' ');
        let indexOfThisAnt = checkPathForAnt(splited, number);
        if(!indexOfThisAnt)
        {
            for (var i = 0; i < splited.length;i++)
                path.push(null);
        }
        else
        {
            splited.forEach(function (part, index) {
                let ant = part.split('-')[0];
                let antNum =ant.slice(1);
                let room= part.split('-')[1];
                if (parseInt(antNum) === number)
                    path.push(room);
                else
                    path.push(null);
            })
        }

    })
    this.path = path;
    return this;
}

function createConnections(info, rooms, indexes) {
    if(indexes['solution'] === 0)
        indexes['solution'] = info.length;
  for(var i = indexes['paths']; i < indexes['solution'];i++)
    {
        let conn1 = info[i].split('-')[0];
        let conn2 = info[i].split('-')[1];
        rooms.forEach(function (room) {
            if(conn1 === room.name)
                room.createConn(conn2);
            else if (conn2 === room.name)
                room.createConn(conn1)
        })
    }
}

function findMainIndexes(arr) {
    let startRoomIndex;
    let indexOfEndRoom;
    let solutionStartIndex = arr.indexOf("") +1;
    let pathsStartingIndex = 0;
    var i = 0;
    while (i < arr.length)
    {
        if(arr[i].includes('##end'))
        {
            indexOfEndRoom = i + 1;
            i++;
        }
        else if(arr[i].includes('##start'))
        {
            startRoomIndex = i +1;
            i++;
        }
        else if (arr[i].includes('-') && !pathsStartingIndex)
            pathsStartingIndex = i;
        i++;
    }

    let res = [];
    res['start'] = startRoomIndex;
    res['end'] = indexOfEndRoom;
    res['paths'] = pathsStartingIndex;
    res['solution'] = solutionStartIndex;
    return res;
}

function parseInfo(text)
{
    let splitted_info = text.split('\r\n');//for Win
   // let splitted_info = text.split('\n');
    if (splitted_info[0] === 'ERROR')
        throw new Error('File is not valid.\nError description: ' + splitted_info[1]);
    else if (splitted_info[0] === '<!DOCTYPE html>')
        throw new Error('File not found');
    let Indexes =findMainIndexes(splitted_info);
    let info = [];
    info['quant_of_ants'] = splitted_info[0];
    let Rooms = [];
    for(var i = 1;i < Indexes['paths'];i++)
    {
        if(i!==Indexes['start'] -1 && i !== Indexes['end'] - 1)
        {
            let opt = null;
            if(i === Indexes['start'])
                opt ="start";
            else if(i === Indexes['end'])
                opt = "end";
            let r = new Room(splitted_info[i], opt);
            if ((r['name'][0] === '#' && opt) || r['name'][0] !== '#')
                Rooms.push(r);
        }

    }
    info['rooms'] = Rooms;
    createConnections(splitted_info, info['rooms'],Indexes);
    let ants = [];
    for(var i =1; i<= parseInt(info['quant_of_ants']);i++)
    {
        ants.push(new Ant(i, splitted_info.slice(Indexes['solution'], splitted_info.length - 1)));
    }
    ants = ants.map(function (ant) {
        if(ant['path'].length === 0)
            ant['path'] = null;
        return ant;
    })
    info['ants'] = ants;
    draw(info);
}


(async () => {
    await fetch(fileName)
        .then(function (response) {
            return response.text();
        })
        .then(function (text) {
            parseInfo(text);
        })
        .catch(function (error) {
            console.log(error);
            let errorHeader = document.createElement("h1");
            errorHeader.classList.add('error-header');
            errorHeader.innerText = error;
            if (error.toString() === "TypeError: Failed to fetch")
                errorHeader.innerText = error.toString() + '\nPlease, start the web-server.'
            if (error.toString() === "TypeError: Reduce of empty array with no initial value")
                errorHeader.innerText = 'File to parse is not found.'

            document.querySelector('body').append(errorHeader);
            container.style.display = "none";
            document.querySelector('.info_about').style.display = 'none';
            document.querySelector('.buttons-container').style.display = 'none';
        })
})();

