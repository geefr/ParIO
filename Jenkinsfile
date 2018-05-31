pipeline {
  agent any

  options {
    buildDiscarder( logRotator(artifactDaysToKeepStr: '90') )
    checkoutToSubdirectory('source')
    timeout(time: 1, unit: 'HOURS')
  }
  triggers { 
    pollSCM('H * * * *') 
  }

  stages {
    stage('Setup') {
      steps {
        sh "mkdir ${env.WORKSPACE}/build"
        sh "mkdir ${env.WORKSPACE}/install"
      }
    }
    stage('Build') {
      steps {
        sh "cd ${env.WORKSPACE}/build"
        sh "cmake -DCMAKE_INSTALL_PREFIX=${env.WORKSPACE}/install ${env.WORKSPACE}/source"
        sh "make install"
      }
    }
  }
}
