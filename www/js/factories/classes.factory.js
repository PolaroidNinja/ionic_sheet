(function() {

    angular.module('sheet')
        .factory('classesFactory', classesFactory);

    //////////////////////////////////////////

    function classesFactory() {
       var _data = {
            "Barbarian": {
                "name": "Barbarian",
                "hit_die": "d12",
                "saving_prof": [
                    "STR",
                    "CON"
                ],
                "armor_prof": "Light armor, medium armor, shields",
                "weapon_prof": "Simple weapons, martial weapons",
                "skills_number": 2,
                "skill_prof": [
                    "Animal Handling",
                    "Athletics",
                    "Intimidation",
                    "Nature",
                    "Perception",
                    "Survival"
                ],
                "levels": [{
                    "level": "1st",
                    "proficiency": 2,
                    "features": "Rage, Unarmored Defense",
                    "rages": 2,
                    "rage_damage": 2
                }, {
                    "level": "2nd",
                    "proficiency": 2,
                    "features": "Reckless Attack, Danger Sense",
                    "rages": 2,
                    "rage_damage": 2
                }, {
                    "level": "3rd",
                    "proficiency": 2,
                    "features": "Primal Path",
                    "rages": 3,
                    "rage_damage": 2
                }, {
                    "level": "4th",
                    "proficiency": 2,
                    "features": "Ability Score Improvement",
                    "rages": 3,
                    "rage_damage": 2
                }, {
                    "level": "5th",
                    "proficiency": 3,
                    "features": "Extra Attack, Fast Movement",
                    "rages": 3,
                    "rage_damage": 2
                }, {
                    "level": "6th",
                    "proficiency": 3,
                    "features": "Path feature",
                    "rages": 4,
                    "rage_damage": 2
                }, {
                    "level": "7th",
                    "proficiency": 3,
                    "features": "Feral Instinct",
                    "rages": 4,
                    "rage_damage": 2
                }, {
                    "level": "8th",
                    "proficiency": 3,
                    "features": "Ability Score Improvement",
                    "rages": 4,
                    "rage_damage": 2
                }, {
                    "level": "9th",
                    "proficiency": 4,
                    "features": "Brutal Critical (1 die)",
                    "rages": 4,
                    "rage_damage": 3
                }, {
                    "level": "10th",
                    "proficiency": 4,
                    "features": "Path feature",
                    "rages": 4,
                    "rage_damage": 3
                }, {
                    "level": "11th",
                    "proficiency": 4,
                    "features": "Relentless Rage",
                    "rages": 4,
                    "rage_damage": 3
                }, {
                    "level": "12th",
                    "proficiency": 4,
                    "features": "Ability Score Improvement",
                    "rages": 5,
                    "rage_damage": 3
                }, {
                    "level": "13th",
                    "proficiency": 5,
                    "features": "Brutal Critical (2 dice)",
                    "rages": 5,
                    "rage_damage": 3
                }, {
                    "level": "14th",
                    "proficiency": 5,
                    "features": "Path feature",
                    "rages": 5,
                    "rage_damage": 3
                }, {
                    "level": "15th",
                    "proficiency": 5,
                    "features": "Persistent Rage",
                    "rages": 5,
                    "rage_damage": 3
                }, {
                    "level": "16th",
                    "proficiency": 5,
                    "features": "Ability Score Improvement",
                    "rages": 5,
                    "rage_damage": 4
                }, {
                    "level": "17th",
                    "proficiency": 6,
                    "features": "Brutal Critical (3 dice)",
                    "rages": 6,
                    "rage_damage": 4
                }, {
                    "level": "18th",
                    "proficiency": 6,
                    "features": "Indomitable Might",
                    "rages": 6,
                    "rage_damage": 4
                }, {
                    "level": "19th",
                    "proficiency": 6,
                    "features": "Ability Score Improvement",
                    "rages": 6,
                    "rage_damage": 4
                }, {
                    "level": "20th",
                    "proficiency": 6,
                    "features": "Primal Champion",
                    "rages": "Unlimited",
                    "rage_damage": 4
                }]
            },
            "Bard": {
                "name": "Bard",
                "hit_die": "d8",
                "saving_prof": [
                    "DEX",
                    "CHA"
                ],
                "armor_prof": "Light armor",
                "weapon_prof": "Simple weapons, hand crossbows, longswords, rapiers, shortswords",
                "skills_number": 3,
                "skill_prof": [],
                "levels": [{
                    "level": "1st",
                    "proficiency": 2,
                    "features": "Spellcasting, Bardic Inspiration (d6)",
                    "cantrips": 2,
                    "spells_known": 4,
                    "spell_slots": [
                        "2",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "2nd",
                    "proficiency": 2,
                    "features": "Jack of All Trades, Song of Rest (d6)",
                    "cantrips": 2,
                    "spells_known": 5,
                    "spell_slots": [
                        "3",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "3rd",
                    "proficiency": 2,
                    "features": "Bard College, Expertise",
                    "cantrips": 2,
                    "spells_known": 6,
                    "spell_slots": [
                        "4",
                        "2",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "4th",
                    "proficiency": 2,
                    "features": "Ability Score Improvement",
                    "cantrips": 3,
                    "spells_known": 7,
                    "spell_slots": [
                        "4",
                        "3",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "5th",
                    "proficiency": 3,
                    "features": "Bardic Inspiration (d8), Font of Inspiration",
                    "cantrips": 3,
                    "spells_known": 8,
                    "spell_slots": [
                        "4",
                        "3",
                        "2",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "6th",
                    "proficiency": 3,
                    "features": "Countercharm, Bard College feature",
                    "cantrips": 3,
                    "spells_known": 9,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "7th",
                    "proficiency": 3,
                    "features": "--",
                    "cantrips": 3,
                    "spells_known": 10,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "1",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "8th",
                    "proficiency": 3,
                    "features": "Ability Score Improvement",
                    "cantrips": 3,
                    "spells_known": 11,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "2",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "9th",
                    "proficiency": 4,
                    "features": "Song of Rest (d8)",
                    "cantrips": 3,
                    "spells_known": 12,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "1",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "10th",
                    "proficiency": 4,
                    "features": "Bardic Inspiration (d10), Expertise, Magical Secrets",
                    "cantrips": 4,
                    "spells_known": 14,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "2",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "11th",
                    "proficiency": 4,
                    "features": "--",
                    "cantrips": 4,
                    "spells_known": 15,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "2",
                        "1",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "12th",
                    "proficiency": 4,
                    "features": "Ability Score Improvement",
                    "cantrips": 4,
                    "spells_known": 15,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "2",
                        "1",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "13th",
                    "proficiency": 5,
                    "features": "Song of Rest (d10)",
                    "cantrips": 4,
                    "spells_known": 16,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "2",
                        "1",
                        "1",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "14th",
                    "proficiency": 5,
                    "features": "Magical Secrets, Bard College feature",
                    "cantrips": 4,
                    "spells_known": 18,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "2",
                        "1",
                        "1",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "15th",
                    "proficiency": 5,
                    "features": "Bardic Inspiration (d12)",
                    "cantrips": 4,
                    "spells_known": 19,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "2",
                        "1",
                        "1",
                        "1",
                        "-"
                    ]
                }, {
                    "level": "16th",
                    "proficiency": 5,
                    "features": "Ability Score Improvement",
                    "cantrips": 4,
                    "spells_known": 19,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "2",
                        "1",
                        "1",
                        "1",
                        "-"
                    ]
                }, {
                    "level": "17th",
                    "proficiency": 6,
                    "features": "Song of Rest (d12)",
                    "cantrips": 4,
                    "spells_known": 20,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "2",
                        "1",
                        "1",
                        "1",
                        "1"
                    ]
                }, {
                    "level": "18th",
                    "proficiency": 6,
                    "features": "Magical Secrets",
                    "cantrips": 4,
                    "spells_known": 22,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "3",
                        "1",
                        "1",
                        "1",
                        "1"
                    ]
                }, {
                    "level": "19th",
                    "proficiency": 6,
                    "features": "Ability Score Improvement",
                    "cantrips": 4,
                    "spells_known": 22,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "3",
                        "2",
                        "1",
                        "1",
                        "1"
                    ]
                }, {
                    "level": "20th",
                    "proficiency": 6,
                    "features": "Superior Inspiration",
                    "cantrips": 4,
                    "spells_known": 22,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "3",
                        "2",
                        "2",
                        "1",
                        "1"
                    ]
                }]
            },
            "Cleric": {
                "name": "Cleric",
                "hit_die": "d8",
                "saving_prof": [
                    "WIS",
                    "CHA"
                ],
                "armor_prof": "Light armor, medium armor, shields",
                "weapon_prof": "All simple weapons",
                "skills_number": 2,
                "skill_prof": [
                    "History",
                    "Insight",
                    "Medicine",
                    "Persuasion",
                    "Religion"
                ],
                "levels": [{
                    "level": "1st",
                    "proficiency": 2,
                    "features": "Spellcasting, Divine Domain",
                    "cantrips": 3,
                    "spell_slots": [
                        "2",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "2nd",
                    "proficiency": 2,
                    "features": "Channel Divinity (1/rest), Divine Domain feature",
                    "cantrips": 3,
                    "spell_slots": [
                        "3",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "3rd",
                    "proficiency": 2,
                    "features": "--",
                    "cantrips": 3,
                    "spell_slots": [
                        "4",
                        "2",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "4th",
                    "proficiency": 2,
                    "features": "Ability Score Improvement",
                    "cantrips": 4,
                    "spell_slots": [
                        "4",
                        "3",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "5th",
                    "proficiency": 3,
                    "features": "Destroy Undead (CR 1/2)",
                    "cantrips": 4,
                    "spell_slots": [
                        "4",
                        "3",
                        "2",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "6th",
                    "proficiency": 3,
                    "features": "Channel Divinity (2/rest), Divine Domain feature",
                    "cantrips": 4,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "7th",
                    "proficiency": 3,
                    "features": "--",
                    "cantrips": 4,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "1",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "8th",
                    "proficiency": 3,
                    "features": "Ability Score Improvement, Destroy Undead (CR 1), Divine Domain feature",
                    "cantrips": 4,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "2",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "9th",
                    "proficiency": 4,
                    "features": "--",
                    "cantrips": 4,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "1",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "10th",
                    "proficiency": 4,
                    "features": "Divine Intervention",
                    "cantrips": 5,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "2",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "11th",
                    "proficiency": 4,
                    "features": "Destroy Undead (CR 2)",
                    "cantrips": 5,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "2",
                        "1",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "12th",
                    "proficiency": 4,
                    "features": "Ability Score Improvement",
                    "cantrips": 5,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "2",
                        "1",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "13th",
                    "proficiency": 5,
                    "features": "--",
                    "cantrips": 5,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "2",
                        "1",
                        "1",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "14th",
                    "proficiency": 5,
                    "features": "Destroy Undead (CR 3)",
                    "cantrips": 5,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "2",
                        "1",
                        "1",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "15th",
                    "proficiency": 5,
                    "features": "--",
                    "cantrips": 5,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "2",
                        "1",
                        "1",
                        "1",
                        "-"
                    ]
                }, {
                    "level": "16th",
                    "proficiency": 5,
                    "features": "Ability Score Improvement",
                    "cantrips": 5,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "2",
                        "1",
                        "1",
                        "1",
                        "-"
                    ]
                }, {
                    "level": "17th",
                    "proficiency": 6,
                    "features": "Destroy Undead (CR 4), Divine Domain feature",
                    "cantrips": 5,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "2",
                        "1",
                        "1",
                        "1",
                        "1"
                    ]
                }, {
                    "level": "18th",
                    "proficiency": 6,
                    "features": "Channel Divinity (3/rest)",
                    "cantrips": 5,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "3",
                        "1",
                        "1",
                        "1",
                        "1"
                    ]
                }, {
                    "level": "19th",
                    "proficiency": 6,
                    "features": "Ability Score Improvement",
                    "cantrips": 5,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "3",
                        "2",
                        "1",
                        "1",
                        "1"
                    ]
                }, {
                    "level": "20th",
                    "proficiency": 6,
                    "features": "Divine Intervention improvement",
                    "cantrips": 5,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "3",
                        "2",
                        "2",
                        "1",
                        "1"
                    ]
                }]
            },
            "Druid": {
                "name": "Druid",
                "hit_die": "d8",
                "saving_prof": [
                    "INT",
                    "WIS"
                ],
                "armor_prof": "Light armor, medium armor, shields (druids will not wear armor or use shields made of metal)",
                "weapon_prof": "Clubs, daggers, darts, javelins, maces, quarterstaffs, scimitars, sickles, slings, spears",
                "skills_number": 2,
                "skill_prof": [
                    "Arcana",
                    "Animal Handling",
                    "Insight",
                    "Medicine",
                    "Nature",
                    "Perception",
                    "Religion",
                    "Survival"
                ],
                "levels": [{
                    "level": "1st",
                    "proficiency": 2,
                    "features": "Druidic, Spellcasting",
                    "cantrips": 2,
                    "spell_slots": [
                        "2",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "2nd",
                    "proficiency": 2,
                    "features": "Wild Shape, Druid Circle",
                    "cantrips": 2,
                    "spell_slots": [
                        "3",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "3rd",
                    "proficiency": 2,
                    "features": "--",
                    "cantrips": 2,
                    "spell_slots": [
                        "4",
                        "2",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "4th",
                    "proficiency": 2,
                    "features": "Wild Shape improvement, Ability Score Improvement",
                    "cantrips": 3,
                    "spell_slots": [
                        "4",
                        "3",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "5th",
                    "proficiency": 3,
                    "features": "--",
                    "cantrips": 3,
                    "spell_slots": [
                        "4",
                        "3",
                        "2",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "6th",
                    "proficiency": 3,
                    "features": "Druid Circle feature",
                    "cantrips": 3,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "7th",
                    "proficiency": 3,
                    "features": "--",
                    "cantrips": 3,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "1",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "8th",
                    "proficiency": 3,
                    "features": "Wild Shape improvement, Ability Score Improvement",
                    "cantrips": 3,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "2",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "9th",
                    "proficiency": 4,
                    "features": "--",
                    "cantrips": 3,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "1",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "10th",
                    "proficiency": 4,
                    "features": "Druid Circle feature",
                    "cantrips": 4,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "2",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "11th",
                    "proficiency": 4,
                    "features": "--",
                    "cantrips": 4,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "2",
                        "1",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "12th",
                    "proficiency": 4,
                    "features": "Ability Score Improvement",
                    "cantrips": 4,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "2",
                        "1",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "13th",
                    "proficiency": 5,
                    "features": "--",
                    "cantrips": 4,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "2",
                        "1",
                        "1",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "14th",
                    "proficiency": 5,
                    "features": "Druid Circle feature",
                    "cantrips": 4,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "2",
                        "1",
                        "1",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "15th",
                    "proficiency": 5,
                    "features": "--",
                    "cantrips": 4,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "2",
                        "1",
                        "1",
                        "1",
                        "-"
                    ]
                }, {
                    "level": "16th",
                    "proficiency": 5,
                    "features": "Ability Score Improvement",
                    "cantrips": 4,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "2",
                        "1",
                        "1",
                        "1",
                        "-"
                    ]
                }, {
                    "level": "17th",
                    "proficiency": 6,
                    "features": "--",
                    "cantrips": 4,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "2",
                        "1",
                        "1",
                        "1",
                        "1"
                    ]
                }, {
                    "level": "18th",
                    "proficiency": 6,
                    "features": "Timeless Body, Beast Spells",
                    "cantrips": 4,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "3",
                        "1",
                        "1",
                        "1",
                        "1"
                    ]
                }, {
                    "level": "19th",
                    "proficiency": 6,
                    "features": "Ability Score Improvement",
                    "cantrips": 4,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "3",
                        "2",
                        "1",
                        "1",
                        "1"
                    ]
                }, {
                    "level": "20th",
                    "proficiency": 6,
                    "features": "Archdruid",
                    "cantrips": 4,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "3",
                        "2",
                        "2",
                        "1",
                        "1"
                    ]
                }]
            },
            "Fighter": {
                "name": "Fighter",
                "hit_die": "d10",
                "saving_prof": [
                    "STR",
                    "CON"
                ],
                "armor_prof": "All armor, shields",
                "weapon_prof": "Simple weapons, martial weapons",
                "skills_number": 2,
                "skill_prof": [
                    "Acrobatics",
                    "Animal Handling",
                    "Athletics",
                    "History",
                    "Insight",
                    "Intimidation",
                    "Perception",
                    "Survival"
                ],
                "levels": [{
                    "level": "1st",
                    "proficiency": 2,
                    "features": "Fighting Style, Second Wind"
                }, {
                    "level": "2nd",
                    "proficiency": 2,
                    "features": "Action Surge (one use)"
                }, {
                    "level": "3rd",
                    "proficiency": 2,
                    "features": "Martial Archetype"
                }, {
                    "level": "4th",
                    "proficiency": 2,
                    "features": "Ability Score Improvement"
                }, {
                    "level": "5th",
                    "proficiency": 3,
                    "features": "Extra Attack"
                }, {
                    "level": "6th",
                    "proficiency": 3,
                    "features": "Ability Score Improvement"
                }, {
                    "level": "7th",
                    "proficiency": 3,
                    "features": "Martial Archetype feature"
                }, {
                    "level": "8th",
                    "proficiency": 3,
                    "features": "Ability Score Improvement"
                }, {
                    "level": "9th",
                    "proficiency": 4,
                    "features": "Indomitable (one use)"
                }, {
                    "level": "10th",
                    "proficiency": 4,
                    "features": "Martial Archetype feature"
                }, {
                    "level": "11th",
                    "proficiency": 4,
                    "features": "Extra Attack (2)"
                }, {
                    "level": "12th",
                    "proficiency": 4,
                    "features": "Ability Score Improvement"
                }, {
                    "level": "13th",
                    "proficiency": 5,
                    "features": "Indomitable (two uses)"
                }, {
                    "level": "14th",
                    "proficiency": 5,
                    "features": "Ability Score Improvement"
                }, {
                    "level": "15th",
                    "proficiency": 5,
                    "features": "Martial Archetype feature"
                }, {
                    "level": "16th",
                    "proficiency": 5,
                    "features": "Ability Score Improvement"
                }, {
                    "level": "17th",
                    "proficiency": 6,
                    "features": "Action Surge (two uses), Indomitable (three uses)"
                }, {
                    "level": "18th",
                    "proficiency": 6,
                    "features": "Martial Archetype feature"
                }, {
                    "level": "19th",
                    "proficiency": 6,
                    "features": "Ability Score Improvement"
                }, {
                    "level": "20th",
                    "proficiency": 6,
                    "features": "Extra Attack (3)"
                }]
            },
            "Monk": {
                "name": "Monk",
                "hit_die": "d8",
                "saving_prof": [
                    "STR",
                    "DEX"
                ],
                "armor_prof": "None",
                "weapon_prof": "Simple weapons, shortswords",
                "skills_number": 2,
                "skill_prof": [
                    "Acrobatics",
                    "Athletics",
                    "History",
                    "Insight",
                    "Religion",
                    "Stealth"
                ],
                "levels": [{
                    "level": "1st",
                    "proficiency": 2,
                    "features": "Unarmored Defense, Martial Arts",
                    "martial_arts": "d4",
                    "ki_points": "--",
                    "unarmored_movement": "--"
                }, {
                    "level": "2nd",
                    "proficiency": 2,
                    "features": "Ki, Unarmored Movement",
                    "martial_arts": "d4",
                    "ki_points": 2,
                    "unarmored_movement": 10
                }, {
                    "level": "3rd",
                    "proficiency": 2,
                    "features": "Monastic Tradition, Deflect Missiles",
                    "martial_arts": "d4",
                    "ki_points": 3,
                    "unarmored_movement": 10
                }, {
                    "level": "4th",
                    "proficiency": 2,
                    "features": "Ability Score Improvement, Slow Fall",
                    "martial_arts": "d4",
                    "ki_points": 4,
                    "unarmored_movement": 10
                }, {
                    "level": "5th",
                    "proficiency": 3,
                    "features": "Extra Attack, Stunning Strike",
                    "martial_arts": "d6",
                    "ki_points": 5,
                    "unarmored_movement": 10
                }, {
                    "level": "6th",
                    "proficiency": 3,
                    "features": "Ki-Empowered Strikes, Monastic Tradition feature",
                    "martial_arts": "d6",
                    "ki_points": 6,
                    "unarmored_movement": 15
                }, {
                    "level": "7th",
                    "proficiency": 3,
                    "features": "Evasion, Stillness of Mind",
                    "martial_arts": "d6",
                    "ki_points": 7,
                    "unarmored_movement": 15
                }, {
                    "level": "8th",
                    "proficiency": 3,
                    "features": "Ability Score Improvement",
                    "martial_arts": "d6",
                    "ki_points": 8,
                    "unarmored_movement": 15
                }, {
                    "level": "9th",
                    "proficiency": 4,
                    "features": "Unarmored Movement improvement",
                    "martial_arts": "d6",
                    "ki_points": 9,
                    "unarmored_movement": 15
                }, {
                    "level": "10th",
                    "proficiency": 4,
                    "features": "Purity of Body",
                    "martial_arts": "d6",
                    "ki_points": 10,
                    "unarmored_movement": 20
                }, {
                    "level": "11th",
                    "proficiency": 4,
                    "features": "Monastic Tradition feature",
                    "martial_arts": "d8",
                    "ki_points": 11,
                    "unarmored_movement": 20
                }, {
                    "level": "12th",
                    "proficiency": 4,
                    "features": "Ability Score Improvement",
                    "martial_arts": "d8",
                    "ki_points": 12,
                    "unarmored_movement": 20
                }, {
                    "level": "13th",
                    "proficiency": 5,
                    "features": "Tongue of the Sun and Moon",
                    "martial_arts": "d8",
                    "ki_points": 13,
                    "unarmored_movement": 20
                }, {
                    "level": "14th",
                    "proficiency": 5,
                    "features": "Diamond Soul",
                    "martial_arts": "d8",
                    "ki_points": 14,
                    "unarmored_movement": 25
                }, {
                    "level": "15th",
                    "proficiency": 5,
                    "features": "Timeless Body",
                    "martial_arts": "d8",
                    "ki_points": 15,
                    "unarmored_movement": 25
                }, {
                    "level": "16th",
                    "proficiency": 5,
                    "features": "Ability Score Improvement",
                    "martial_arts": "d8",
                    "ki_points": 16,
                    "unarmored_movement": 25
                }, {
                    "level": "17th",
                    "proficiency": 6,
                    "features": "Monastic Tradition feature",
                    "martial_arts": "d10",
                    "ki_points": 17,
                    "unarmored_movement": 25
                }, {
                    "level": "18th",
                    "proficiency": 6,
                    "features": "Empty Body",
                    "martial_arts": "d10",
                    "ki_points": 18,
                    "unarmored_movement": 30
                }, {
                    "level": "19th",
                    "proficiency": 6,
                    "features": "Ability Score Improvement",
                    "martial_arts": "d10",
                    "ki_points": 19,
                    "unarmored_movement": 30
                }, {
                    "level": "20th",
                    "proficiency": 6,
                    "features": "Perfect Self",
                    "martial_arts": "d10",
                    "ki_points": 20,
                    "unarmored_movement": 30
                }]
            },
            "Paladin": {
                "name": "Paladin",
                "hit_die": "d10",
                "saving_prof": [
                    "WIS",
                    "CHA"
                ],
                "armor_prof": "All armor, shields",
                "weapon_prof": "Simple weapons, martial weapons",
                "skills_number": 2,
                "skill_prof": [
                    "Athletics",
                    "Insight",
                    "Intimidation",
                    "Medicine",
                    "Persuasion",
                    "Religion"
                ],
                "levels": [{
                    "level": "1st",
                    "proficiency": 2,
                    "features": "Divine Sense, Lay on Hands",
                    "spell_slots": [
                        "-",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "2nd",
                    "proficiency": 2,
                    "features": "Fighting Style, Spellcasting, Divine Smite",
                    "spell_slots": [
                        "2",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "3rd",
                    "proficiency": 2,
                    "features": "Divine Health, Sacred Oath",
                    "spell_slots": [
                        "3",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "4th",
                    "proficiency": 2,
                    "features": "Ability Score Improvement",
                    "spell_slots": [
                        "3",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "5th",
                    "proficiency": 3,
                    "features": "Extra Attack",
                    "spell_slots": [
                        "4",
                        "2",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "6th",
                    "proficiency": 3,
                    "features": "Aura of Protection",
                    "spell_slots": [
                        "4",
                        "2",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "7th",
                    "proficiency": 3,
                    "features": "Sacred Oath feature",
                    "spell_slots": [
                        "4",
                        "3",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "8th",
                    "proficiency": 3,
                    "features": "Ability Score Improvement",
                    "spell_slots": [
                        "4",
                        "3",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "9th",
                    "proficiency": 4,
                    "features": "--",
                    "spell_slots": [
                        "4",
                        "3",
                        "2",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "10th",
                    "proficiency": 4,
                    "features": "Aura of Courage",
                    "spell_slots": [
                        "4",
                        "3",
                        "2",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "11th",
                    "proficiency": 4,
                    "features": "Improved Divine Smite",
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "12th",
                    "proficiency": 4,
                    "features": "Ability Score Improvement",
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "13th",
                    "proficiency": 5,
                    "features": "--",
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "1",
                        "-"
                    ]
                }, {
                    "level": "14th",
                    "proficiency": 5,
                    "features": "Cleansing Touch",
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "1",
                        "-"
                    ]
                }, {
                    "level": "15th",
                    "proficiency": 5,
                    "features": "Sacred Oath feature",
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "2",
                        "-"
                    ]
                }, {
                    "level": "16th",
                    "proficiency": 5,
                    "features": "Ability Score Improvement",
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "2",
                        "-"
                    ]
                }, {
                    "level": "17th",
                    "proficiency": 6,
                    "features": "--",
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "1"
                    ]
                }, {
                    "level": "18th",
                    "proficiency": 6,
                    "features": "Aura improvements",
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "1"
                    ]
                }, {
                    "level": "19th",
                    "proficiency": 6,
                    "features": "Ability Score Improvement",
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "2"
                    ]
                }, {
                    "level": "20th",
                    "proficiency": 6,
                    "features": "Sacred Oath feature",
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "2"
                    ]
                }]
            },
            "Ranger": {
                "name": "Ranger",
                "hit_die": "d10",
                "saving_prof": [
                    "STR",
                    "DEX"
                ],
                "armor_prof": "Light armor, medium armor, shields",
                "weapon_prof": "Simple weapons, martial weapons",
                "skills_number": 3,
                "skill_prof": [
                    "Animal Handling",
                    "Athletics",
                    "Insight",
                    "Investigation",
                    "Nature",
                    "Perception",
                    "Stealth",
                    "Survival"
                ],
                "levels": [{
                    "level": "1st",
                    "proficiency": 2,
                    "features": "Favored Enemy, Natural Explorer",
                    "spells_known": "--",
                    "spell_slots": [
                        "-",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "2nd",
                    "proficiency": 2,
                    "features": "Fighting Style, Spellcasting",
                    "spells_known": 2,
                    "spell_slots": [
                        "2",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "3rd",
                    "proficiency": 2,
                    "features": "Ranger Archetype, Primeval Awareness",
                    "spells_known": 3,
                    "spell_slots": [
                        "3",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "4th",
                    "proficiency": 2,
                    "features": "Ability Score Improvement",
                    "spells_known": 3,
                    "spell_slots": [
                        "3",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "5th",
                    "proficiency": 3,
                    "features": "Extra Attack",
                    "spells_known": 4,
                    "spell_slots": [
                        "4",
                        "2",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "6th",
                    "proficiency": 3,
                    "features": "Favored Enemy and Natural Explorer improvements",
                    "spells_known": 4,
                    "spell_slots": [
                        "4",
                        "2",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "7th",
                    "proficiency": 3,
                    "features": "Ranger Archetype feature",
                    "spells_known": 5,
                    "spell_slots": [
                        "4",
                        "3",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "8th",
                    "proficiency": 3,
                    "features": "Ability Score Improvement, Land's Stride",
                    "spells_known": 5,
                    "spell_slots": [
                        "4",
                        "3",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "9th",
                    "proficiency": 4,
                    "features": "--",
                    "spells_known": 6,
                    "spell_slots": [
                        "4",
                        "3",
                        "2",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "10th",
                    "proficiency": 4,
                    "features": "Natural Explorer improvement, Hide in Plain Sight",
                    "spells_known": 6,
                    "spell_slots": [
                        "4",
                        "3",
                        "2",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "11th",
                    "proficiency": 4,
                    "features": "Ranger Archetype feature",
                    "spells_known": 7,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "12th",
                    "proficiency": 4,
                    "features": "Ability Score Improvement",
                    "spells_known": 7,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "13th",
                    "proficiency": 5,
                    "features": "--",
                    "spells_known": 8,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "1",
                        "-"
                    ]
                }, {
                    "level": "14th",
                    "proficiency": 5,
                    "features": "Favored Enemy improvement, Vanish",
                    "spells_known": 8,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "1",
                        "-"
                    ]
                }, {
                    "level": "15th",
                    "proficiency": 5,
                    "features": "Ranger Archetype feature",
                    "spells_known": 9,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "2",
                        "-"
                    ]
                }, {
                    "level": "16th",
                    "proficiency": 5,
                    "features": "Ability Score Improvement",
                    "spells_known": 9,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "2",
                        "-"
                    ]
                }, {
                    "level": "17th",
                    "proficiency": 6,
                    "features": "--",
                    "spells_known": 10,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "1"
                    ]
                }, {
                    "level": "18th",
                    "proficiency": 6,
                    "features": "Feral Senses",
                    "spells_known": 10,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "1"
                    ]
                }, {
                    "level": "19th",
                    "proficiency": 6,
                    "features": "Ability Score Improvement",
                    "spells_known": 11,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "2"
                    ]
                }, {
                    "level": "20th",
                    "proficiency": 6,
                    "features": "Foe Slayer",
                    "spells_known": 11,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "2"
                    ]
                }]
            },
            "Rogue": {
                "name": "Rogue",
                "hit_die": "d8",
                "saving_prof": [
                    "DEX",
                    "INT"
                ],
                "armor_prof": "Light armor",
                "weapon_prof": "Simple weapons, hand crossbows, longswords, rapiers, shortswords",
                "skills_number": 4,
                "skill_prof": [
                    "Acrobatics",
                    "Athletics",
                    "Deception",
                    "Insight",
                    "Intimidation",
                    "Investigation",
                    "Perception",
                    "Performance",
                    "Persuasion",
                    "Sleight of Hand",
                    "Stealth"
                ],
                "levels": [{
                    "level": "1st",
                    "proficiency": 2,
                    "features": "Expertise, Sneak Attack, Thievesâ€™ Cant",
                    "sneak_attack": "1d6"
                }, {
                    "level": "2nd",
                    "proficiency": 2,
                    "features": "Cunning Action",
                    "sneak_attack": "1d6"
                }, {
                    "level": "3rd",
                    "proficiency": 2,
                    "features": "Roguish Archetype",
                    "sneak_attack": "2d6"
                }, {
                    "level": "4th",
                    "proficiency": 2,
                    "features": "Ability Score Improvement",
                    "sneak_attack": "2d6"
                }, {
                    "level": "5th",
                    "proficiency": 3,
                    "features": "Uncanny Dodge",
                    "sneak_attack": "3d6"
                }, {
                    "level": "6th",
                    "proficiency": 3,
                    "features": "Expertise",
                    "sneak_attack": "3d6"
                }, {
                    "level": "7th",
                    "proficiency": 3,
                    "features": "Evasion",
                    "sneak_attack": "4d6"
                }, {
                    "level": "8th",
                    "proficiency": 3,
                    "features": "Ability Score Improvement",
                    "sneak_attack": "4d6"
                }, {
                    "level": "9th",
                    "proficiency": 4,
                    "features": "Roguish Archetype feature",
                    "sneak_attack": "5d6"
                }, {
                    "level": "10th",
                    "proficiency": 4,
                    "features": "Ability Score Improvement",
                    "sneak_attack": "5d6"
                }, {
                    "level": "11th",
                    "proficiency": 4,
                    "features": "Reliable Talent",
                    "sneak_attack": "6d6"
                }, {
                    "level": "12th",
                    "proficiency": 4,
                    "features": "Ability Score Improvement",
                    "sneak_attack": "6d6"
                }, {
                    "level": "13th",
                    "proficiency": 5,
                    "features": "Roguish Archetype feature",
                    "sneak_attack": "7d6"
                }, {
                    "level": "14th",
                    "proficiency": 5,
                    "features": "Blindsense",
                    "sneak_attack": "7d6"
                }, {
                    "level": "15th",
                    "proficiency": 5,
                    "features": "Slippery Mind",
                    "sneak_attack": "8d6"
                }, {
                    "level": "16th",
                    "proficiency": 5,
                    "features": "Ability Score Improvement",
                    "sneak_attack": "8d6"
                }, {
                    "level": "17th",
                    "proficiency": 6,
                    "features": "Roguish Archetype feature",
                    "sneak_attack": "9d6"
                }, {
                    "level": "18th",
                    "proficiency": 6,
                    "features": "Elusive",
                    "sneak_attack": "9d6"
                }, {
                    "level": "19th",
                    "proficiency": 6,
                    "features": "Ability Score Improvement",
                    "sneak_attack": "10d6"
                }, {
                    "level": "20th",
                    "proficiency": 6,
                    "features": "Stroke of Luck",
                    "sneak_attack": "10d6"
                }]
            },
            "Sorcerer": {
                "name": "Sorcerer",
                "hit_die": "d6",
                "saving_prof": [
                    "CON",
                    "CHA"
                ],
                "armor_prof": "None",
                "weapon_prof": "Daggers, darts, slings, quarterstaffs, light crossbows",
                "skills_number": 2,
                "skill_prof": [
                    "Arcana",
                    "Deception",
                    "Insight",
                    "Intimidation",
                    "Persuasion",
                    "Religion"
                ],
                "levels": [{
                    "level": "1st",
                    "proficiency": 2,
                    "features": "Spellcasting, Sorcerous Origin",
                    "points": "--",
                    "cantrips": 4,
                    "spells_known": 2,
                    "spell_slots": [
                        "2",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "2nd",
                    "proficiency": 2,
                    "features": "Font of Magic",
                    "points": 2,
                    "cantrips": 4,
                    "spells_known": 3,
                    "spell_slots": [
                        "3",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "3rd",
                    "proficiency": 2,
                    "features": "Metamagic",
                    "points": 3,
                    "cantrips": 4,
                    "spells_known": 4,
                    "spell_slots": [
                        "4",
                        "2",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "4th",
                    "proficiency": 2,
                    "features": "Ability Score Improvement",
                    "points": 4,
                    "cantrips": 5,
                    "spells_known": 5,
                    "spell_slots": [
                        "4",
                        "3",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "5th",
                    "proficiency": 3,
                    "features": "--",
                    "points": 5,
                    "cantrips": 5,
                    "spells_known": 6,
                    "spell_slots": [
                        "4",
                        "3",
                        "2",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "6th",
                    "proficiency": 3,
                    "features": "Sorcerous Origin feature",
                    "points": 6,
                    "cantrips": 5,
                    "spells_known": 7,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "7th",
                    "proficiency": 3,
                    "features": "--",
                    "points": 7,
                    "cantrips": 5,
                    "spells_known": 8,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "1",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "8th",
                    "proficiency": 3,
                    "features": "Ability Score Improvement",
                    "points": 8,
                    "cantrips": 5,
                    "spells_known": 9,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "2",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "9th",
                    "proficiency": 4,
                    "features": "--",
                    "points": 9,
                    "cantrips": 5,
                    "spells_known": 10,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "1",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "10th",
                    "proficiency": 4,
                    "features": "Metamagic",
                    "points": 10,
                    "cantrips": 6,
                    "spells_known": 11,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "2",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "11th",
                    "proficiency": 4,
                    "features": "--",
                    "points": 11,
                    "cantrips": 6,
                    "spells_known": 12,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "2",
                        "1",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "12th",
                    "proficiency": 4,
                    "features": "Ability Score Improvement",
                    "points": 12,
                    "cantrips": 6,
                    "spells_known": 12,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "2",
                        "1",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "13th",
                    "proficiency": 5,
                    "features": "--",
                    "points": 13,
                    "cantrips": 6,
                    "spells_known": 13,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "2",
                        "1",
                        "1",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "14th",
                    "proficiency": 5,
                    "features": "Sorcerous Origin feature",
                    "points": 14,
                    "cantrips": 6,
                    "spells_known": 13,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "2",
                        "1",
                        "1",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "15th",
                    "proficiency": 5,
                    "features": "--",
                    "points": 15,
                    "cantrips": 6,
                    "spells_known": 14,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "2",
                        "1",
                        "1",
                        "1",
                        "-"
                    ]
                }, {
                    "level": "16th",
                    "proficiency": 5,
                    "features": "Ability Score Improvement",
                    "points": 16,
                    "cantrips": 6,
                    "spells_known": 14,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "2",
                        "1",
                        "1",
                        "1",
                        "-"
                    ]
                }, {
                    "level": "17th",
                    "proficiency": 6,
                    "features": "Metamagic",
                    "points": 17,
                    "cantrips": 6,
                    "spells_known": 15,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "2",
                        "1",
                        "1",
                        "1",
                        "1"
                    ]
                }, {
                    "level": "18th",
                    "proficiency": 6,
                    "features": "Sorcerous Origin feature",
                    "points": 18,
                    "cantrips": 6,
                    "spells_known": 15,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "3",
                        "1",
                        "1",
                        "1",
                        "1"
                    ]
                }, {
                    "level": "19th",
                    "proficiency": 6,
                    "features": "Ability Score Improvement",
                    "points": 19,
                    "cantrips": 6,
                    "spells_known": 15,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "3",
                        "2",
                        "1",
                        "1",
                        "1"
                    ]
                }, {
                    "level": "20th",
                    "proficiency": 6,
                    "features": "Sorcerous Restoration",
                    "points": 20,
                    "cantrips": 6,
                    "spells_known": 15,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "3",
                        "2",
                        "2",
                        "1",
                        "1"
                    ]
                }]
            },
            "Warlock": {
                "name": "Warlock",
                "hit_die": "d8",
                "saving_prof": [
                    "WIS",
                    "CHA"
                ],
                "armor_prof": "Light armor",
                "weapon_prof": "Simple weapons",
                "skills_number": 2,
                "skill_prof": [
                    "Arcana",
                    "Deception",
                    "History",
                    "Intimidation",
                    "Investigation",
                    "Nature",
                    "Religion"
                ],
                "levels": [{
                    "level": "1st",
                    "proficiency": 2,
                    "features": "Otherworldly Patron, Pact Magic",
                    "cantrips": 2,
                    "spells_known": 2,
                    "spell_slots": 1,
                    "slot_level": 1,
                    "invocations": "--"
                }, {
                    "level": "2nd",
                    "proficiency": 2,
                    "features": "Eldritch Invocations",
                    "cantrips": 2,
                    "spells_known": 3,
                    "spell_slots": 2,
                    "slot_level": 1,
                    "invocations": 2
                }, {
                    "level": "3rd",
                    "proficiency": 2,
                    "features": "Pact Boon",
                    "cantrips": 2,
                    "spells_known": 4,
                    "spell_slots": 2,
                    "slot_level": 2,
                    "invocations": 2
                }, {
                    "level": "4th",
                    "proficiency": 2,
                    "features": "Ability Score Improvement",
                    "cantrips": 3,
                    "spells_known": 5,
                    "spell_slots": 2,
                    "slot_level": 2,
                    "invocations": 2
                }, {
                    "level": "5th",
                    "proficiency": 3,
                    "features": "--",
                    "cantrips": 3,
                    "spells_known": 6,
                    "spell_slots": 2,
                    "slot_level": 3,
                    "invocations": 3
                }, {
                    "level": "6th",
                    "proficiency": 3,
                    "features": "Otherworldly Patron feature",
                    "cantrips": 3,
                    "spells_known": 7,
                    "spell_slots": 2,
                    "slot_level": 3,
                    "invocations": 3
                }, {
                    "level": "7th",
                    "proficiency": 3,
                    "features": "--",
                    "cantrips": 3,
                    "spells_known": 8,
                    "spell_slots": 2,
                    "slot_level": 4,
                    "invocations": 4
                }, {
                    "level": "8th",
                    "proficiency": 3,
                    "features": "Ability Score Improvement",
                    "cantrips": 3,
                    "spells_known": 9,
                    "spell_slots": 2,
                    "slot_level": 4,
                    "invocations": 4
                }, {
                    "level": "9th",
                    "proficiency": 4,
                    "features": "--",
                    "cantrips": 3,
                    "spells_known": 10,
                    "spell_slots": 2,
                    "slot_level": 5,
                    "invocations": 5
                }, {
                    "level": "10th",
                    "proficiency": 4,
                    "features": "Otherworldly Patron feature",
                    "cantrips": 4,
                    "spells_known": 10,
                    "spell_slots": 2,
                    "slot_level": 5,
                    "invocations": 5
                }, {
                    "level": "11th",
                    "proficiency": 4,
                    "features": "Mystic Arcanum (6th level)",
                    "cantrips": 4,
                    "spells_known": 11,
                    "spell_slots": 3,
                    "slot_level": 5,
                    "invocations": 5
                }, {
                    "level": "12th",
                    "proficiency": 4,
                    "features": "Ability Score Improvement",
                    "cantrips": 4,
                    "spells_known": 11,
                    "spell_slots": 3,
                    "slot_level": 5,
                    "invocations": 6
                }, {
                    "level": "13th",
                    "proficiency": 5,
                    "features": "Mystic Arcanum (7th level)",
                    "cantrips": 4,
                    "spells_known": 12,
                    "spell_slots": 3,
                    "slot_level": 5,
                    "invocations": 6
                }, {
                    "level": "14th",
                    "proficiency": 5,
                    "features": "Otherworldly Patron feature",
                    "cantrips": 4,
                    "spells_known": 12,
                    "spell_slots": 3,
                    "slot_level": 5,
                    "invocations": 6
                }, {
                    "level": "15th",
                    "proficiency": 5,
                    "features": "Mystic Arcanum (8th level)",
                    "cantrips": 4,
                    "spells_known": 13,
                    "spell_slots": 3,
                    "slot_level": 5,
                    "invocations": 7
                }, {
                    "level": "16th",
                    "proficiency": 5,
                    "features": "Ability Score Improvement",
                    "cantrips": 4,
                    "spells_known": 13,
                    "spell_slots": 3,
                    "slot_level": 5,
                    "invocations": 7
                }, {
                    "level": "17th",
                    "proficiency": 6,
                    "features": "Mystic Arcanum (9th level)",
                    "cantrips": 4,
                    "spells_known": 14,
                    "spell_slots": 4,
                    "slot_level": 5,
                    "invocations": 7
                }, {
                    "level": "18th",
                    "proficiency": 6,
                    "features": "--",
                    "cantrips": 4,
                    "spells_known": 14,
                    "spell_slots": 4,
                    "slot_level": 5,
                    "invocations": 8
                }, {
                    "level": "19th",
                    "proficiency": 6,
                    "features": "Ability Score Improvement",
                    "cantrips": 4,
                    "spells_known": 15,
                    "spell_slots": 4,
                    "slot_level": 5,
                    "invocations": 8
                }, {
                    "level": "20th",
                    "proficiency": 6,
                    "features": "Eldritch Master",
                    "cantrips": 4,
                    "spells_known": 15,
                    "spell_slots": 4,
                    "slot_level": 5,
                    "invocations": 8
                }]
            },
            "Wizard": {
                "name": "Wizard",
                "hit_die": "d6",
                "saving_prof": [
                    "INT",
                    "WIS"
                ],
                "armor_prof": "None",
                "weapon_prof": "Daggers, darts, slings, quarterstaffs, light crossbows",
                "skills_number": 2,
                "skill_prof": [
                    "Arcana",
                    "History",
                    "Insight",
                    "Investigation",
                    "Medicine",
                    "Religion"
                ],
                "levels": [{
                    "level": "1st",
                    "proficiency": 2,
                    "features": "Spellcasting, Arcane Recovery",
                    "cantrips": 3,
                    "spell_slots": [
                        "2",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "2nd",
                    "proficiency": 2,
                    "features": "Arcane Tradition",
                    "cantrips": 3,
                    "spell_slots": [
                        "3",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "3rd",
                    "proficiency": 2,
                    "features": "--",
                    "cantrips": 3,
                    "spell_slots": [
                        "4",
                        "2",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "4th",
                    "proficiency": 2,
                    "features": "Ability Score Improvement",
                    "cantrips": 4,
                    "spell_slots": [
                        "4",
                        "3",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "5th",
                    "proficiency": 3,
                    "features": "--",
                    "cantrips": 4,
                    "spell_slots": [
                        "4",
                        "3",
                        "2",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "6th",
                    "proficiency": 3,
                    "features": "Arcane Tradition feature",
                    "cantrips": 4,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "7th",
                    "proficiency": 3,
                    "features": "--",
                    "cantrips": 4,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "1",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "8th",
                    "proficiency": 3,
                    "features": "Ability Score Improvement",
                    "cantrips": 4,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "2",
                        "-",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "9th",
                    "proficiency": 4,
                    "features": "--",
                    "cantrips": 4,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "1",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "10th",
                    "proficiency": 4,
                    "features": "Arcane Tradition feature",
                    "cantrips": 5,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "2",
                        "-",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "11th",
                    "proficiency": 4,
                    "features": "--",
                    "cantrips": 5,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "2",
                        "1",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "12th",
                    "proficiency": 4,
                    "features": "Ability Score Improvement",
                    "cantrips": 5,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "2",
                        "1",
                        "-",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "13th",
                    "proficiency": 5,
                    "features": "--",
                    "cantrips": 5,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "2",
                        "1",
                        "1",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "14th",
                    "proficiency": 5,
                    "features": "Arcane Tradition feature",
                    "cantrips": 5,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "2",
                        "1",
                        "1",
                        "-",
                        "-"
                    ]
                }, {
                    "level": "15th",
                    "proficiency": 5,
                    "features": "--",
                    "cantrips": 5,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "2",
                        "1",
                        "1",
                        "1",
                        "-"
                    ]
                }, {
                    "level": "16th",
                    "proficiency": 5,
                    "features": "Ability Score Improvement",
                    "cantrips": 5,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "2",
                        "1",
                        "1",
                        "1",
                        "-"
                    ]
                }, {
                    "level": "17th",
                    "proficiency": 6,
                    "features": "--",
                    "cantrips": 5,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "2",
                        "1",
                        "1",
                        "1",
                        "1"
                    ]
                }, {
                    "level": "18th",
                    "proficiency": 6,
                    "features": "Spell Mastery",
                    "cantrips": 5,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "3",
                        "1",
                        "1",
                        "1",
                        "1"
                    ]
                }, {
                    "level": "19th",
                    "proficiency": 6,
                    "features": "Ability Score Improvement",
                    "cantrips": 5,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "3",
                        "2",
                        "1",
                        "1",
                        "1"
                    ]
                }, {
                    "level": "20th",
                    "proficiency": 6,
                    "features": "Signature Spell",
                    "cantrips": 5,
                    "spell_slots": [
                        "4",
                        "3",
                        "3",
                        "3",
                        "3",
                        "2",
                        "2",
                        "1",
                        "1"
                    ]
                }]
            }
        };
        
        return {
           data: _data
        };
    }

})();