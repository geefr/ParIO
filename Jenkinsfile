pipeline {
  agent any

properties([pipelineTriggers([[$class: 'GitHubPushTrigger'], pollSCM('H/15 * * * *')])])

  options {
    buildDiscarder( logRotator(artifactDaysToKeepStr: '90') )
    checkoutToSubdirectory('source')
    timeout(time: 1, unit: 'HOURS')
  }

  stages {
    stage('CMake') { steps {
      dir("${env.WORKSPACE}/build") {
        sh '''cmake -DCMAKE_INSTALL_PREFIX=../install ../source'''
      }
    } }
    stage('Build') {
      steps {
        dir("${env.WORKSPACE}/build") {
          sh '''make install'''
        }
      }
    }
    stage('Artifacts') {
      steps {
          sh '''tar -cvzf ParIO.tar.gz install/*'''
archiveArtifacts artifacts: 'ParIO.tar.gz', fingerprint: true, onlyIfSuccessful: true
      }
    }
  }
}
