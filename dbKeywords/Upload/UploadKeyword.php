<?php
    include('dbconnection.php');

    
    if(isset($_POST['submit'])){
        $definition = $_POST['definition'];
        $syntaxis = $_POST['syntaxis'];
        $keyword_name = $_POST['Keyword_name'];
        $keyword_type = $_POST['Keyword_type'];
        $example = $_POST['example'];
        $keyword_cpp_version = $_POST['Keyword_cpp_standart'];
        $keyword_related_keywords = $_POST['Related_keyword'];

        mysqli_set_charset($con, 'utf8');

        $query = mysqli_query($con, "INSERT INTO keyword (Name, Definition, Syntaxis, Type, Example, cpp_version, Related_keywords) VALUES ('$keyword_name', '$definition', '$syntaxis', '$keyword_type', '$example', '$keyword_cpp_version', '$keyword_related_keywords')");
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
        <style>
            input[name="definition"]{
                width: 100%;
                height: 10%;
            }
            textarea[name="syntaxis"],
            textarea[name="example"] {
            width: 100%;
            height: 100px;
        }
        </style>
        <label>Keyword name:</label>
            <select name="Keyword_name">
            <?php
                include('dbconnection.php');
                $keyword_name_dropdown = mysqli_query($con, "SELECT * FROM keywordname");
                while($c = mysqli_fetch_array($keyword_name_dropdown)){
            ?>
                <option value="<?php echo $c['Keyword_name'] ?>"><?php echo $c['Keyword_name'] ?></option>
            <?php } ?>
            </select>
            <br/> <br />

            <input type="text" name="definition" placeholder="Enter keyword definition"/>
            <br/> <br />

            <input type="textarea" name="syntaxis" placeholder="Enter keyword syntaxis"/>
            
            <br/><br/>
            <label>Keyword type:</label>
            <select name="Keyword_type">
            <option value=""></option>
            <?php
                include('dbconnection.php');
                $keyword_type_dropdown = mysqli_query($con, "SELECT * FROM type");
                while($c = mysqli_fetch_array($keyword_type_dropdown)){
            ?>
                    <option value="<?php echo $c['Keyword_type'] ?>"><?php echo $c['Keyword_type'] ?></option>
            <?php } ?>
        </select>            <br/><br/>
            
             <input type="text" name="example" placeholder="Enter keyword example"/>
            <br/> <br />

            <label>C++ version:</label>
            <select name="Keyword_cpp_standart">
            <?php
                include('dbconnection.php');
                $keyword_cpp_dropdown = mysqli_query($con, "SELECT * FROM cpp_standart");
                while($c = mysqli_fetch_array($keyword_cpp_dropdown)){
            ?>
            <option value="<?php echo $c['standart_version'] ?>"><?php echo $c['standart_version'] ?></option>
            <?php } ?>
            </select>
            <br/><br/>

            <label>Related keywords:</label>
            <input type="text" name="Related_keyword" placeholder="Enter related keywords"/>
            <br/><br/>
            </select>
            <button type="submit" name="submit">Submit</button>
            </form>
        </div>
    </body>
</html>