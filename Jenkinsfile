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
    stage('Setup') { steps {
sh '''mkdir -p ${env.WORKSPACE}/build
mkdir -p ${env.WORKSPACE}/install'''
    } }
    stage('CMake') { steps {
sh '''cd ${env.WORKSPACE}/build
cmake -DCMAKE_INSTALL_PREFIX=${env.WORKSPACE}/install ${env.WORKSPACE}/source
'''
    } }
    stage('Build') {
      steps {
sh '''make install'''
      }
    }
    stage('Package') {
      steps {
        sh "tar -cvzf ${env.WORKSPACE}/ParIO.tar.gz ${env.WORKSPACE}/install/*"

archiveArtifacts artifacts: '${env.WORKSPACE}/ParIO.tar.gz', fingerprint: true, onlyIfSuccessful: true
      }
    }
  }
}
