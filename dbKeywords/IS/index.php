<?php
    include 'header.php'
?>

<link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/water.css@2/out/light.css">

<form action="search.php" method="POST">
    
    <input type="text" name="search" placeholder="Input keyword data">
    
    <button type="submit" name="submit-search">Search</button>
</form>

<!DOCTYPE html>
<html>
<head>
    <title>Home</title>
    <meta charset="UTF-8">
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/water.css@2/out/light.css">
</head>
<body>
    
    <button class="home-button" onclick="location.href='http://localhost/dbKeywords/Authentification/index.php'">Home</button>
    
</body>
</html>

<h1>C++ keywords</h1>
<div class="article-container">
<?php
$sql = "SELECT keyword.Name, COUNT(*) AS count 
        FROM example 
        JOIN keyword ON example.Text LIKE CONCAT('%', keyword.Name, '%')
        GROUP BY keyword.Name
        ORDER BY count DESC
        LIMIT 3";

        $result = mysqli_query($conn, $sql);
        echo "<h2>Most popular keywords used in our examples: </h2>";
        
        while ($row = mysqli_fetch_assoc($result)) {
            echo "<div class='top-words-list'>";
            echo "<a href='article.php?title=".$row['Name']."'>";
            echo "<span class='keyword-name'>".$row['Name']." (".$row['count'].")</span>";
            echo "</a>";
            echo "</div>";
        }
?>

<h2>All keywords:</h2>

<div class="words-container">
    <?php
        $sql = "SELECT * FROM keyword";
        $result = mysqli_query($conn, $sql);
        $queryResults = mysqli_num_rows($result);

        if ($queryResults > 0){
            while ($row = mysqli_fetch_assoc($result)) {
                echo "<div class='words-list'><a href='article.php?title=".$row['Name']."&type=".$row['Type']."'> 
                <div class='article-box'>
                <h3>".$row['Name']."</h3>
                <p class='type'>".$row['Type']."</p>
                </div>
                </div>";
            }
        }
    ?>
</div>

</body>
</html>