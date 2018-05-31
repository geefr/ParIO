pipeline {
  agent any

  options {
    buildDiscarder( logRotator(artifactDaysToKeepStr: '90') )
    checkoutToSubdirectory('source')
    timestamps
    timeout(time: 1, unit: 'HOURS')
  }
  triggers { 
    pollSCM('H * * * *') 
  }

  stages {
    stage('Setup') {
      mkdir ${env.WORKSPACE}/build
      mkdir ${env.WORKSPACE}/install
    }
    stage('Build') {
      steps {
        sh "cd ${env.WORKSPACE}/build"
        sh "cmake -DCMAKE_INSTALL_PREFIX=${env.WORKSPACE}/install ${env.WORKSPACE}/source"
        sh "make install"
      }
    }
    stage('Deploy') {
      steps {
        echo 'Deploying....'
      }
    }
  }
}
