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
        cd ${env.WORKSPACE}/build
        cmake -DCMAKE_INSTALL_PREFIX=${env.WORKSPACE}/install ${env.WORKSPACE}
        make install
      }
    }
    stage('Deploy') {
      steps {
        echo 'Deploying....'
      }
    }
  }
}
