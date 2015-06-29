(function() {
    
    angular.module('sheet')
    .config(sheetConfigs);
    
    angular.module('sheet')
    .constant('NEW_CHARACTER_TEMPLATE', {
        uid: null,
        name: "Unnamed Character",
        class: "No Class",
        stats: {
            "strength": { "score": 10, "order": 0},
            "dexterity": { "score": 10, "order": 1},
            "constitution": { "score": 10, "order": 2},
            "intelligence": { "score": 10, "order": 3},
            "wisdom": { "score": 10, "order": 4},
            "charisma": { "score": 10, "order": 5}
        },
        level: 1,
        combat: {
            hp: {
                current: null,
                max: 0,
                temp: 0
            },
            hitDice: {
                current: 1,
                type: null
            },
            death: {
                successes: [1,0,0],
                failures: [0,0,0],
            },
            ac: 10
        },
        proficiencies: {
            skills: null,
            saves: null,
            tools: null,
            weapons: null,
            armor: null,
            other: null
        },
        background: {
            name: null,
            trait: null,
            personality: null,
            flaw: null,
            bonds: null
        },
        equipment: null,
        spells: null
    });


    /////////////////////////////
    //sheetConfigs.$inject['$stateProvider', '$urlRouterProvider'];
    function sheetConfigs ($stateProvider, $urlRouterProvider) {
        $stateProvider

          .state('app', {
              url: "/app",
              abstract: true,
              templateUrl: "templates/menu.html",
              controller: 'sheetCTRL as vm'
          })
          
          .state('app.roller', {
              url: "/roller",
              views: {
                  'menuContent': {
                      templateUrl: "templates/roller.html"
                  }
              }
          })
          
          .state('app.classes', {
                  url: "/classes",
                  views: {
                      'menuContent': {
                          templateUrl: "templates/classes.html"
                      }
                  }
              })
              .state('app.characters', {
                  url: "/characters",
                  views: {
                      'menuContent': {
                          templateUrl: "templates/characters.html",
                      }
                  }
              })
          
          .state('app.single', {
              url: "/characters/:characterId",
              views: {
                  'menuContent': {
                      templateUrl: "templates/character_view.html",
                      controller: "characterCTRL as vm"
                  }
              }
          });
          // if none of the above states are matched, use this as the fallback
          $urlRouterProvider.otherwise('/app/characters');
    }
})();