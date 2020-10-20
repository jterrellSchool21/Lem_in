var connect = require('connect');
var serveStatic = require('serve-static');
var fs = require('fs');
var opn = require('opn');

const getData = (fileName, type) =>
    new Promise((resolve, reject) =>
        fs.readFile(fileName, type, (err, data) => {
            return err ? reject(err) : resolve(data);
        })
    );

if(process.argv[2] != null && process.argv[2] != undefined)
{
    let result = "let fileName = \'" + process.argv[2] + "\';";
    try{
        fs.writeFileSync('filename.js', result);
    }catch (e){
        console.log("Cannot write file ", e);
    }
    getData(process.argv[2], 'utf8')
        .then(text =>
        {
            connect()
                .use(serveStatic(__dirname))
                .listen(8000, () => {console.log("\x1b[32m%s\x1b[0m" ,'Visualiser running on http://localhost:8000')
                });
                opn('http://localhost:8000');

                })
        .catch(error => console.log('Error: ', error));
}
else
    console.log("\x1b[31m%s\x1b[0m", 'Error!No file to visualise');
