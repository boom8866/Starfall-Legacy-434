-- Phasemask update for Isiset (id: 39587) in zone: 4945, area: 4945
UPDATE `creature` SET `phasemask` = 2 WHERE `guid` = 218703;

-- Phasemask update for Ammunae (id: 39731) in zone: 4945, area: 4945
UPDATE `creature` SET `phasemask` = 2 WHERE `guid` = 218344;

-- Phasemask update for Occu'thar (id: 52363) in zone: 5600, area: 5600
UPDATE `creature` SET `phasemask` = 2 WHERE `guid` = 103;

-- Phasemask update for Disciple of Hate (id: 56350) in zone: 5600, area: 5600
UPDATE `creature` SET `phasemask` = 2 WHERE `guid` = 85;

-- Phasemask update for Disciple of Hate (id: 56350) in zone: 5600, area: 5600
UPDATE `creature` SET `phasemask` = 2 WHERE `guid` = 110;

-- Phasemask update for Alizabal (id: 55869) in zone: 5600, area: 5600
UPDATE `creature` SET `phasemask` = 2 WHERE `guid` = 112;

DELETE FROM `disables` WHERE `comment` IN
('Lost City of the Tol\'vir (4.0) - Close',
'The Deadmines (4.0) - Close',
'Throne of the four Winds (4.0) - Close',
'Shadowfang Keep (4.0) - Close',
'Stonecore (4.0) - Close',
'Bastion of Twliight (4.0) - Close');

