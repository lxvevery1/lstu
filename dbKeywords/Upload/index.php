<?php
    include 'dbconnection.php'
    
?>



<!DOCTYPE html>
<html>
<head>
    <title>Home-upload</title>
    <meta charset="UTF-8">
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/water.css@2/out/light.css">
    <style>
        .home-button {
            position: absolute;
            top: 10px;
            left: 10px;
            padding: 10px;
            font-size: 16px;
            background-color: #d5d5d5;
            color: black;
            border: none;
            cursor: pointer;
            width: 150px;
        }
    </style>
</head>
<body>
    <button class="home-button" onclick="location.href='http://localhost/dbKeywords/Authentification/index.php'">Home</button>
    
    <h1>Upload</h1>
    <br><button onclick="location.href='http://localhost/dbKeywords/Upload/UploadKeywordName.php'">Upload Keyword Name</button></br>
    <br><button onclick="location.href='http://localhost/dbKeywords/Upload/UploadType.php'">Upload Type</button></br>
    <br><button onclick="location.href='http://localhost/dbKeywords/Upload/UploadC++Standart.php'">Upload C++ Standart</button></br>
    <br><button onclick="location.href='http://localhost/dbKeywords/Upload/UploadExample.php'">Upload Example</button></br>
    <br><br><button onclick="location.href='http://localhost/dbKeywords/Upload/UploadKeyword.php'">Upload Keyword</button></br></br>
    
    
    
</body>
</html>