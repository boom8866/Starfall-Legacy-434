-- Milhouse Manastorm
UPDATE `creature_template` SET `minlevel`= 83, `maxlevel`= 83 WHERE `entry`= 43391;
UPDATE `creature_template` SET `minlevel`= 86, `maxlevel`= 86, `faction_A`= 16, `faction_H`= 16, `exp`= 3 WHERE `entry`= 49653;

-- Main Trash
UPDATE `creature_template` SET `minlevel`= 82, `maxlevel`= 82 WHERE `entry` IN (42696, 43430, 43537, 43662, 42808, 42845, 42695, 42691, 42789);
UPDATE `creature_template` SET `minlevel`= 85, `maxlevel`= 85, `faction_A`= 16, `faction_H`= 16, `exp`= 3 WHERE `entry` IN (49667, 49660, 49662, 49669, 49663, 49655, 49666, 49665, 49664);

-- Crystalspawn Giant and Stonecore Bruiser
UPDATE `creature_template` SET `minlevel`= 83, `maxlevel`= 83 WHERE `entry` IN (42810, 42692, 42428);
UPDATE `creature_template` SET `minlevel`= 86, `maxlevel`= 86, `faction_A`= 16, `faction_H`= 16, `exp`= 3 WHERE `entry` IN (49647, 49661, 49648);
