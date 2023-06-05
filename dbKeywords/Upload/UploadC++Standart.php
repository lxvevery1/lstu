<?php
    include('dbconnection.php');
    if(isset($_POST['submit'])){
        $name = $_POST['name'];

        mysqli_set_charset($con, 'utf8');

        $query = mysqli_query($con, "Insert into cpp_standart (standart_version) Values ('$name')");
        if ($query){
            echo "<script>alert('Data inserted successfully')</script>";
        }
        else {
            echo "<script>alert('There is an error')</script>";
        }
    }
?>

<link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/water.css@2/out/light.css">

<!DOCTYPE html>
<html>
<head>
    <title>Home-upload</title>
    <meta charset="UTF-8">
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

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Insert Data (keyword name) to db</title>
</head>
<body>
    <div style="margin: 5px auto">
        <form method="POST">
            <input type="text" name="name" style="width: 400px;" placeholder="Enter c++ standart (ex: c++11)"/>
            <br/><br/>
            <button type="submit" name="submit" style="font-size: 16px; padding: 10px 20px; ">Submit</button>
        </form>
    </div>
</body>
</html>