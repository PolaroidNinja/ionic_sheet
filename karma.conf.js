// Karma configuration

module.exports = function(config) {
    config.set({

        // base path that will be used to resolve all patterns (eg. files, exclude)
        basePath: '',

        // frameworks to use
        // available frameworks: https://npmjs.org/browse/keyword/karma-adapter
        frameworks: ['mocha', 'chai', 'sinon'],


        // list of files / patterns to load in the browser
        files: [
            'tests/testMain.js',
            {pattern: 'tests/js/**/*.spec.js'},
            {pattern: 'www/js/**/*.js'},
            {pattern: 'www/templates/**/*.html'},
        ],


        // list of files to exclude
        // exclude: [
        //     'src/public/bower_components/**/*test.js'
        // ],


        // preprocess matching files before serving them to the browser
        // available preprocessors: https://npmjs.org/browse/keyword/karma-preprocessor
        // preprocessors: {
        //     'src/config/requirejs.json': ['html2js'],
        //     'test/fixtures/public/js/**/*.html': ['html2js'],
        //     'test/fixtures/public/js/**/*.json': ['html2js'],
        //     'src/public/js/!(wdpr-ui-components-plus)/**/*.js': ['coverage']
        // },


        // test results reporter to use
        // possible values: 'dots', 'progress', 'mocha'
        // available reporters: https://npmjs.org/browse/keyword/karma-reporter
        // reporters: ['mocha','coverage'],


        // web server port
        port: process.env.PORT,
        hostname: process.env.IP,


        // enable / disable colors in the output (reporters and logs)
        colors: true,


        // level of logging
        // possible values: config.LOG_DISABLE || config.LOG_ERROR || config.LOG_WARN || config.LOG_INFO || config.LOG_DEBUG
        //logLevel: config.LOG_INFO,


        // enable / disable watching file and executing tests whenever any file changes
        autoWatch: false,


        // start these browsers
        // available browser launchers: https://npmjs.org/browse/keyword/karma-launcher
        browsers: ['PhantomJS'],


        // Continuous Integration mode
        // if true, Karma captures browsers, runs the tests and exits
        singleRun: true,

        // capture console.log
        client: {
            captureConsole: true
        },
        
        runnerPort: 0

        // coverage reporter options.
        // If no filename is given, it will write the output to the console.
        // coverageReporter : {
        //     dir: 'coverage/',
        //     reporters: [
        //         { type: 'html'},
        //         { type: 'text-summary'}
        //     ]
        // }
    });
};
