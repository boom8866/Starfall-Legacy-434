
REPLACE INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(6444, 'at_chogall_intro');

UPDATE `creature_template` SET `scriptname`= 'boss_chogall' WHERE `entry`= 43324;

REPLACE INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(43324, 7, 0, 'Foolish mortals-(Usurper''s children!) nothing you have done- (Spawn of a lesser god!) I am TRYING to speak here. (Words, words, words. The Master wants murder.) ALL falls to chaos. ALL will be destroyed. (Chaos, chaos!) Your work here today changes nothing. (Chaos, chaos, all things end) No mortal may see what you have and live. Your end has come.', 14, 0, 100, 0, 0, 22068, 'Cho''gall - Cho''gall Intro'),
(43324, 8, 0, 'Enough! (To His will all flesh succumbs. From His kingdom, chaos comes.) Yes - what he said.', 14, 0, 100, 0, 0, 22081, 'Cho''gall - Aggro');

UPDATE `creature` SET `phaseMask`= 1 WHERE `id`= 43324;
DELETE FROM `creature_template_addon` WHERE `entry`= 43324;
