CREATE DATABASE `room_data`;

CREATE TABLE `desired_temp` (
  `id` int NOT NULL AUTO_INCREMENT,
  `desired_temp` float NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB;

CREATE TABLE `temp_data` (
  `id` int NOT NULL AUTO_INCREMENT,
  `temp_in` float NOT NULL,
  `temp_out` float NOT NULL,
  `timestamp` timestamp NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB;