DELETE FROM conditions WHERE SourceEntry IN (75657, 94970, 89124, 75702, 89889);

REPLACE INTO conditions(`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`SourceId`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionTarget`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`NegativeCondition`,`ErrorTextId`,`ScriptName`,`Comment`) VALUES
(13, 7, 75657, 0, 0, 31, 0, 3, 39731, 0, 0, 0, '', ''),
(13, 7, 94970, 0, 0, 31, 0, 3, 39731, 0, 0, 0, '', ''),
(13, 7, 89124, 0, 0, 31, 0, 3, 39731, 0, 0, 0, '', ''),
(13, 2, 75702, 0, 0, 31, 0, 3, 39731, 0, 0, 0, '', ''),
(13, 2, 89889, 0, 0, 31, 0, 3, 39731, 0, 0, 0, '', '');

REPLACE INTO creature_text (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(39731, 0, 0, 'This chamber will flourish with your life energy!', 14, 0, 100, 0, 0, 18571, 'Ammunae'),
(39731, 1, 0, 'Your life, UNLEASHED!', 14, 0, 100, 0, 0, 18572, 'Ammunae'),
(39731, 2, 0, 'Wither away!', 14, 0, 100, 0, 0, 18573, 'Ammunae'),
(39731, 2, 1, 'Waste of energy!', 14, 0, 100, 0, 0, 18574, 'Ammunae'),
(39731, 3, 0, 'The cycle continues...', 14, 0, 100, 0, 0, 18569, 'Ammunae');
