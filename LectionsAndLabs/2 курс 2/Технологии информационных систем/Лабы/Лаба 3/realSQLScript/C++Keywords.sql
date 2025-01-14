-- MySQL Script generated by MySQL Workbench
-- Thu May  4 12:17:38 2023
-- Model: New Model    Version: 1.0
-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

-- -----------------------------------------------------
-- Schema keywords C++
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema keywords C++
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `keywords C++` DEFAULT CHARACTER SET utf8 ;
USE `keywords C++` ;

-- -----------------------------------------------------
-- Table `keywords C++`.`Пример`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `keywords C++`.`Пример` (
  `Номер` INT NOT NULL AUTO_INCREMENT,
  `Текст` VARCHAR(2000) NOT NULL,
  PRIMARY KEY (`Номер`),
  CONSTRAINT `Пример`
    FOREIGN KEY (`Номер`)
    REFERENCES `keywords C++`.`Ключевое Слово` (`Номер`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `keywords C++`.`Ключевое Слово`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `keywords C++`.`Ключевое Слово` (
  `Идентификатор` VARCHAR(45) NOT NULL,
  `Определение` VARCHAR(600) NOT NULL,
  `Синтаксис` VARCHAR(1000) NOT NULL,
  `Тип` VARCHAR(20) NULL,
  `Номер` INT NOT NULL,
  PRIMARY KEY (`Идентификатор`),
  INDEX `Номер_idx` (`Номер` ASC) VISIBLE,
  CONSTRAINT `Номер`
    FOREIGN KEY (`Номер`)
    REFERENCES `keywords C++`.`Пример` (`Номер`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
