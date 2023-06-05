<?php
    $con = mysqli_connect("localhost", "root", "", "keywordsdb");   
    if ($con == false)
    {
        die("Connection error". mysqli_connect_error());
    }
?>