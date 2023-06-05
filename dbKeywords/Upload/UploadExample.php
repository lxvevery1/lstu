<?php
    include('dbconnection.php');

    if(isset($_POST['submit'])){
        $number = $_POST['number'];
        $text = $_POST['text'];
        $keyword_name = $_POST['Keyword_name'];

        mysqli_set_charset($con, 'utf8');

        $query = mysqli_query($con, "INSERT INTO example (Number, Text, Keyword_name) VALUES ('$number', '$text', '$keyword_name')");
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
    <title>Insert Data (keyword example) to db</title>
</head>
<body>
    <div style = "margin: 5px auto">
        <form method = "POST">
            <input type="int" name="number" placeholder="Enter example number"/>
            <br/> <br />
            <input type="text" name="text" placeholder="Enter example text"/>
            <br/> <br />
            <lable>Keyword name:</lable>
            <select name="Keyword_name">
            <?php
                include('dbconnection.php');
                $categories = mysqli_query($con, "SELECT * FROM keywordname");
                while($c = mysqli_fetch_array($categories)){
            ?>
                <option value="<?php echo $c['Keyword_name'] ?>"><?php echo $c['Keyword_name'] ?></option>
            <?php } ?>
            </select>
            <button type="submit" name="submit">Submit</button>
        </form>
    </div> 
</body>
</html>